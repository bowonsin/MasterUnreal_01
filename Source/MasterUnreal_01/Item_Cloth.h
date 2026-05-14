// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Cloth.generated.h"

/**
 * 
 */
UCLASS()
class MASTERUNREAL_01_API AItem_Cloth : public AItemBase
{
	GENERATED_BODY()
public:
	AItem_Cloth();
	virtual void OnFireDected_Implementation(float Temperature, FVector HitLocation) override;
protected:
	// 사용할 파티클 임팩트
	UPROPERTY(EditAnywhere,Category = "Effects")
	TObjectPtr<class UParticleSystem> FireEffects;
	
};
