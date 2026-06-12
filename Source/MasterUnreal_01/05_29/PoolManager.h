// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObjectData.h"
#include "PoolManager.generated.h"

UCLASS()
class MASTERUNREAL_01_API APoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pool")
	TArray<FPooledObjectData> PoolData;

};
