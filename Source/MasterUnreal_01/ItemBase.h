// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyInterface.h"
#include "GameFramework/Actor.h"

#include "TestMyInterface.h"
#include "ItemBase.generated.h"

UCLASS()
class MASTERUNREAL_01_API AItemBase : public AActor , public ITestMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	
	virtual void BeginPlay() override;


	UFUNCTION()
	void PlayerDeathReceive(AController* InstigatorController);

};

/* 
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		UMyActorComponent* HealthComp =	PlayerCharacter->FindComponentByClass<UMyActorComponent>();
		if (HealthComp)
		{
			HealthComp->OnHealthDead.AddDynamic(this, &AItemBase::PlayerDeathReceive);
		}
		else
		{
			//안됐다....
		}
	}
}

void AItemBase::PlayerDeathReceive(AController* InstigatorController)
{
	Destroy();

}
*/