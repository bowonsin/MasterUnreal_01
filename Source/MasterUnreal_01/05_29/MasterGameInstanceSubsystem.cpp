// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterGameInstanceSubsystem.h"
#include "InstanceObjectPool.h"
#include "MyObjectPool.h"
#include "Engine/World.h"

void UMasterGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UWorld* World = GetPoolWorld();

	if (!World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;

	for (int32 PoolIndex = 0;PoolIndex < PooledObjectData.Num();PoolIndex++)
	{
		FSingleObjectPoolInstance CurrentPool;
		SpawnParams.Name =FName(*PooledObjectData[PoolIndex].ActorName);
		SpawnParams.NameMode =FActorSpawnParameters::ESpawnActorNameMode::Requested;
		SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int32 ObjectIndex = 0;ObjectIndex < PooledObjectData[PoolIndex].PoolSize;ObjectIndex++)
		{
			AActor* SpawnedActor =World->SpawnActor<AActor>(
					PooledObjectData[PoolIndex].ActorTemplate,
					FVector::ZeroVector,
					FRotator::ZeroRotator,
					SpawnParams);
			UInstanceObjectPool* PoolComp =NewObject<UInstanceObjectPool>(SpawnedActor);
			// 등록
			PoolComp->RegisterComponent();
			// InstanceCompoent 등록
			SpawnedActor->AddInstanceComponent(PoolComp);
			//
			CurrentPool.PooledObjects.Add(PoolComp);
			// 기능 비활성화 
			SpawnedActor->SetActorHiddenInGame(true);
			SpawnedActor->SetActorEnableCollision(false);
			SpawnedActor->SetActorTickEnabled(false);
		}

		Pools.Add(CurrentPool);
	}
}

void UMasterGameInstanceSubsystem::InitializePool()
{
	UWorld* World = GetPoolWorld();

	if (!World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;

	for (int32 PoolIndex = 0;PoolIndex < PooledObjectData.Num();PoolIndex++)
	{
		FSingleObjectPoolInstance CurrentPool;
		SpawnParams.Name =FName(*PooledObjectData[PoolIndex].ActorName);
		SpawnParams.NameMode =FActorSpawnParameters::ESpawnActorNameMode::Requested;
		SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int32 ObjectIndex = 0;ObjectIndex < PooledObjectData[PoolIndex].PoolSize;ObjectIndex++)
		{
			AActor* SpawnedActor =World->SpawnActor<AActor>(
					PooledObjectData[PoolIndex].ActorTemplate,
					FVector::ZeroVector,
					FRotator::ZeroRotator,
					SpawnParams);
			UInstanceObjectPool* PoolComp =NewObject<UInstanceObjectPool>(SpawnedActor);
			// 등록
			PoolComp->RegisterComponent();
			// InstanceCompoent 등록
			SpawnedActor->AddInstanceComponent(PoolComp);
			//
			CurrentPool.PooledObjects.Add(PoolComp);
			// 기능 비활성화 
			SpawnedActor->SetActorHiddenInGame(true);
			SpawnedActor->SetActorEnableCollision(false);
			SpawnedActor->SetActorTickEnabled(false);
		}

		Pools.Add(CurrentPool);
	}
}

void UMasterGameInstanceSubsystem::Deinitialize()
{
	Broadcast_PoolerCleanup();

	Pools.Empty();

	Super::Deinitialize();
}

AActor* UMasterGameInstanceSubsystem::GetPooledActor(const FString& Name)
{
	int32 CurrentPoolIndex = Pools.Num();

	for (int32 i = 0; i < PooledObjectData.Num(); i++)
	{
		if (PooledObjectData[i].ActorName == Name)
		{
			CurrentPoolIndex = i;
			break;
		}
	}

	if (CurrentPoolIndex == INDEX_NONE)
	{
		return nullptr;
	}

	for (UInstanceObjectPool* PoolObj :
		Pools[CurrentPoolIndex].PooledObjects)
	{
		if (!PoolObj)
		{
			continue;
		}

		if (!PoolObj->bIsPoolActive)
		{
			PoolObj->bIsPoolActive = true;
			AActor* ResultActor =PoolObj->GetOwner();
			
			OnPoolerCleanup.AddUniqueDynamic(PoolObj,&UInstanceObjectPool::RecycleSelf);
			
			ResultActor->SetActorHiddenInGame(false);
			ResultActor->SetActorEnableCollision(true);
			ResultActor->SetActorTickEnabled(true);
			
			return ResultActor;
		}
	}
	return nullptr;
}

void UMasterGameInstanceSubsystem::RecycleActor(AActor* PooledActor)
{
	if (!PooledActor)
	{
		return;
	}
	if (UInstanceObjectPool* PoolCompRef = Cast<UInstanceObjectPool>(PooledActor->GetComponentByClass(UInstanceObjectPool::StaticClass())))
    	{
    		RecyclePooledObject(PoolCompRef);
    	}
}

void UMasterGameInstanceSubsystem::RecyclePooledObject(UInstanceObjectPool* PoolCompRef)
{
	//회수하기
	OnPoolerCleanup.RemoveDynamic(PoolCompRef, &UInstanceObjectPool::RecycleSelf);
	
	//비사용중
	PoolCompRef->bIsPoolActive = false;
	//안보이게 만들기
	AActor* ReturningActor = PoolCompRef->GetOwner();
	if (!ReturningActor)
	{
		return;
	}
	ReturningActor->SetActorHiddenInGame(true);
	ReturningActor->SetActorEnableCollision(false);
	ReturningActor->SetActorTickEnabled(false);
}

void UMasterGameInstanceSubsystem::Broadcast_PoolerCleanup()
{
	OnPoolerCleanup.Broadcast();
}

void UMasterGameInstanceSubsystem::RegenItem(int32 PoolIndex, int32 PositionIndex)
{
	//스폰 준비
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(FString::Printf(TEXT("%s"), *PooledObjectData[PoolIndex].ActorName));
	SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	// 스폰 강제. 항상 스폰
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedActor = GetWorld()->SpawnActor(PooledObjectData[PoolIndex].ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);
	if (!SpawnedActor)
	{
		return;
	}
	SpawnedActor->SetActorLabel(SpawnedActor->GetName());
	UInstanceObjectPool* PoolComp = NewObject<UInstanceObjectPool>(SpawnedActor);
	PoolComp->RegisterComponent();
	SpawnedActor->AddInstanceComponent(PoolComp);
	
	Pools[PoolIndex].PooledObjects.Insert(PoolComp, PositionIndex);
	SpawnedActor->SetActorHiddenInGame(true);
	SpawnedActor->SetActorEnableCollision(false);
	SpawnedActor->SetActorTickEnabled(false);
}

UWorld* UMasterGameInstanceSubsystem::GetPoolWorld() const
{
	if (GetGameInstance())
	{
		return GetGameInstance()->GetWorld();
	}

	return nullptr;
}
