// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StudyActor.generated.h"

UCLASS()
class MASTERUNREAL_01_API AStudyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStudyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartSingleTrace();

	void StartAsyncTarce();

	// 이게 델리게이트 인자이다
	void OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

};
