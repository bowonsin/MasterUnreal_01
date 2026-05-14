// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// 컴포넌트와 Kismet...static 사용해야한다.
#include "Kismet/GameplayStatics.h"
#include "MyActorComponent.h"
#include "GameFramework/Character.h"
// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 월드에서 0번쨰 케릭터를 가져와 달라는 함수
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	
	if (PlayerCharacter)
	{
		UMyActorComponent* HealthComp = PlayerCharacter->FindComponentByClass<UMyActorComponent>();
		if (HealthComp)
		{
			HealthComp->OnHealthDead.AddDynamic(this, &AItemBase::PlayerDeathReceive);
		}
		else
		{
			// 안됐다.
		}
	}
}

void AItemBase::PlayerDeathReceive(AController* InstigatorController)
{
	Destroy();
}

