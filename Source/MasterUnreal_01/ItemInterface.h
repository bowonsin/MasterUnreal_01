// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class MASTERUNREAL_01_API IItemInterface
{
	GENERATED_BODY()

public:

	// 아이템 존제 유무만 확인할 수 있으면 되지 않을 까 합니다 .
	// 딱히 기능을 넣지 않을 예정

	//virtual void OnItemOverlap(AActor* overlapActor) = 0;
	//virtual void OnItemEndOverlap(AActor* overlapActor) = 0;
	//virtual void ActivateItem(AActor* Activator) = 0;

	// FName 은 타입형으로 하기 떄문에 
	virtual FName GetItemType() const = 0;
};
