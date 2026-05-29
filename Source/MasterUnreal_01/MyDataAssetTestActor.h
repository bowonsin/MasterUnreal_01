// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/AssetManager.h"  // 필수
#include "MyDataAssetTestActor.generated.h"

UCLASS()
class MASTERUNREAL_01_API AMyDataAssetTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDataAssetTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ID를 가지고있다가
	//로드되면 여기에 저장한다.
	//아이디를 넣어주는 곳,
	UPROPERTY(EditAnywhere, Category = "ItemTest")
	FPrimaryAssetId ItemToLoad;

	UPROPERTY(VisibleAnywhere, Category = "ItemTest")
	class UMyItemData* LoadedItem;

	//최초로 실행될 함수
	void StartLoading();

	//AssetManager
	TSharedPtr<FStreamableHandle> LoadingHandle;
	void OnLoadFinished(FPrimaryAssetId LoadedId);
};
