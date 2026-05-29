// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyWeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AActor> WeaponClass;
};
