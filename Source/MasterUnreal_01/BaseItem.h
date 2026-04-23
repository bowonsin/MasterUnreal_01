// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"


UCLASS()
class MASTERUNREAL_01_API ABaseItem : public AActor ,public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	void SetTitle(FName name);
	const FName GetTitleName();

protected:
	// Called when the game starts or when spawned


	virtual FName GetItemType() const override;

	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Item")
	FName ItemType;

};
