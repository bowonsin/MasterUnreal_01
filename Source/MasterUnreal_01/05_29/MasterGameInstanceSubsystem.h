#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PooledObjectData.h"
#include "MasterGameInstanceSubsystem.generated.h"

class UInstanceObjectPool;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature_a);

UCLASS()
class MASTERUNREAL_01_API UMasterGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	void InitializePool();
	virtual void Deinitialize() override;

	AActor* GetPooledActor(const FString& Name);

	UFUNCTION(BlueprintCallable)
	void RecycleActor(AActor* PooledActor);

	UFUNCTION(BlueprintCallable)
	void RecyclePooledObject(UInstanceObjectPool* PoolCompRef);

	UFUNCTION(BlueprintCallable)
	void Broadcast_PoolerCleanup();

	UPROPERTY()
	FPoolerCleanupSignature_a OnPoolerCleanup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPooledObjectData> PooledObjectData;

protected:

	UPROPERTY()
	TArray<FSingleObjectPoolInstance> Pools;

private:

	void RegenItem(int32 PoolIndex, int32 PositionIndex);

	UWorld* GetPoolWorld() const;
};
