// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MASTERUNREAL_01_API UMyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
};
