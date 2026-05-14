// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"



// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth= MaxHealth;
	// 이름을 굳이 곧대로 박는게 가독성이 좋다.
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UMyActorComponent::DamageTake);
}

void UMyActorComponent::DamageTake(
	AActor* DamageActor
	, float Damage
	, const UDamageType* DamageType
	,AController* Instigator
	, AActor* Cuaser)
{
	// 0이하로 안빠지게 최종데미지를 넣어주는겁니다.
	float FinalDamage = FMath::Min(Damage, CurrentHealth);
	
	CurrentHealth -= FinalDamage;
	
	//
	OnHealthDamaged.Broadcast(CurrentHealth,MaxHealth,FinalDamage);
	if (CurrentHealth <= 0.0f)
	{
		// Instigator는 떄린 actor의 정보를 가져오는 것이다.
		//
		OnHealthDead.Broadcast(Instigator);
	}
}
void UMyActorComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	//TickCompoennt는 무조껀 Super::TickComponent를 꼭 써야한다.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GEngine->AddOnScreenDebugMessage(-1,0.f,FColor::Green,FString::Printf(TEXT("HP : %f"), CurrentHealth));
}
