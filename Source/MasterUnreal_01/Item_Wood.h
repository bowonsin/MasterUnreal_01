// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Wood.generated.h"

/**
 * 
 */
UCLASS()
class MASTERUNREAL_01_API AItem_Wood : public AItemBase
{
	GENERATED_BODY()
public:
	AItem_Wood();
	virtual void OnFireDected_Implementation(float Temperature, FVector HitLocation)override;
protected:
	// 사용할 파티클 임팩트
	UPROPERTY(EditAnywhere,Category = "Effects")
	TObjectPtr<class UParticleSystem> FireEffects;
	
};
