#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InstanceObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERUNREAL_01_API UInstanceObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInstanceObjectPool();
public:

	UPROPERTY()
	bool bIsPoolActive = false;

	UFUNCTION()
	void RecycleSelf();
		
};
