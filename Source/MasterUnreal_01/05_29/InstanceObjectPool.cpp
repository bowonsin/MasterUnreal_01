// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceObjectPool.h"
#include "MasterGameInstanceSubsystem.h"

UInstanceObjectPool::UInstanceObjectPool()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInstanceObjectPool::RecycleSelf()
{
	UWorld* World = GetWorld();

	if (!World)	{return;}
	UGameInstance* GameInstance =World->GetGameInstance();
	if (!GameInstance)	{return;}
	UMasterGameInstanceSubsystem* Pool =GameInstance->GetSubsystem<UMasterGameInstanceSubsystem>();
	if (!Pool){return;}
	Pool->RecyclePooledObject(this);
}