// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WeaponBox.generated.h"

UCLASS()
class MASTERUNREAL_01_API AWeaponBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;

	void OpenBox();
	
	void OpenAsynBox();
	void OnWeaponSpawnDeffered(TSoftClassPtr<AActor> WeaponPtr);
	
};
