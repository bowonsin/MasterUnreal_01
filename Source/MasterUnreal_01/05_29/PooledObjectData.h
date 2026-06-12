#pragma once

#include "CoreMinimal.h"
#include "PooledObjectData.generated.h"

USTRUCT(BlueprintType)
struct FPooledObjectData
{
	GENERATED_BODY()
	
	FPooledObjectData()
	{
		ActorTemplate = nullptr;
		PoolSize = 1;
		bCanGrow = false;
		ActorName = "default";
	}
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorTemplate;

	UPROPERTY(EditAnywhere)
	int32 PoolSize;

	UPROPERTY(EditAnywhere)
	bool bCanGrow;
	
	UPROPERTY(EditAnywhere)
	FString ActorName;
};

USTRUCT(BlueprintType)
struct FSingleObjectPool
{
	GENERATED_BODY()
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class UPooledObject>> PooledObjects;
	//TArray<UPooledObject*> PooledObjectsPool; 이 형태랑 같다고 보면 됨.. 
};
USTRUCT(BlueprintType)
struct FSingleObjectPoolInstance
{
	GENERATED_BODY()
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class UInstanceObjectPool>> PooledObjects;
};