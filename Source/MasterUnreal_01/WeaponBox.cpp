// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBox.h"
#include "MyWeaponStruct.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Sets default values
AWeaponBox::AWeaponBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBox::BeginPlay()
{
	Super::BeginPlay();
	OpenBox();	
}

// Called every frame
void AWeaponBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBox::OpenBox()
{
	if (!WeaponTable) return ;
	
	TArray<FWeaponData *> AllWeapons;
	//AllWeapons 에다가 WeaponTable의 DataTable의 데이터를 다 넣겟다
	WeaponTable->GetAllRows<FWeaponData>(TEXT(""),AllWeapons);
	
	if (AllWeapons.Num()== 0)return;
	
	// 랜덤안 확률로 weapon선택
	FWeaponData* SelectedWeapon = AllWeapons[FMath::RandRange(0,AllWeapons.Num()-1)];
	
	// 선택한 웨폰이 있는지 확인
	if (SelectedWeapon)
	{
		// Weapon Class 호출
		UClass* LoadedClass = SelectedWeapon->WeaponClass.LoadSynchronous();

		if (LoadedClass)
		{
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<AActor>(
				LoadedClass
				, GetActorLocation() + FVector(0, 0, 100)
				, FRotator::ZeroRotator
				, SpawnParams);
			
			GEngine->AddOnScreenDebugMessage(
				-1
				,5.f
				,FColor::Green
				,FString::Printf(TEXT("소환완료 : %s")
				, *SelectedWeapon->WeaponName));
		}
	}
}

void AWeaponBox::OpenAsynBox()
{
	if (!WeaponTable) return ;
	
	TArray<FWeaponData *> AllWeapons;
	//AllWeapons 에다가 WeaponTable의 DataTable의 데이터를 다 넣겟다
	WeaponTable->GetAllRows<FWeaponData>(TEXT(""),AllWeapons);
	
	if (AllWeapons.Num()== 0)return;
	
	// 랜덤안 확률로 weapon선택
	FWeaponData* SelectedWeapon = AllWeapons[FMath::RandRange(0,AllWeapons.Num()-1)];
	
	// 선택한 웨폰이 있는지 확인
	if (SelectedWeapon)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(SelectedWeapon->WeaponClass.ToSoftObjectPath()
			,FStreamableDelegate::CreateUObject(
				this,
				&AWeaponBox::OnWeaponSpawnDeffered,
				SelectedWeapon->WeaponClass
				));
	}
}

void AWeaponBox::OnWeaponSpawnDeffered(TSoftClassPtr<AActor> WeaponPtr)
{
}
