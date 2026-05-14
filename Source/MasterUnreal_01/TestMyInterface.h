// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestMyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTestMyInterface : public UInterface
{
	GENERATED_BODY()
};

class MASTERUNREAL_01_API ITestMyInterface
{
	GENERATED_BODY()
public:
	//  = 0 을 붙이면 상속받을때 무조건 이 함수가 만들어라! 강제하는 
	// 순수 강상함수
	// 블루 프린트를 사용하기 위해서는 가상함수를 사용하지 못한다.
	// 이제부터 Excute를 사용하면 인식이 가능하다.
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent , Category="Interface")
	void OnFireDected(float Temperature, FVector HitLocation);
};
