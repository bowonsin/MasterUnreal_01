// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager.h"
#include "MasterGameInstanceSubsystem.h"

// Sets default values
APoolManager::APoolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolManager::BeginPlay()
{
	Super::BeginPlay();
	UMasterGameInstanceSubsystem* PoolSubsystem =
		GetGameInstance()->GetSubsystem<UMasterGameInstanceSubsystem>();

	if (!PoolSubsystem)
	{
		return;
	}

	PoolSubsystem->PooledObjectData = PoolData;
	PoolSubsystem->InitializePool();
}
