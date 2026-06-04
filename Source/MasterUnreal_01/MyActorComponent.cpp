// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"



// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
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
	
	// 1. 여기서 위젯을 한 번만 생성합니다.
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport(); // 화면에 추가!
		}
	}
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
	
	if (HUDWidgetInstance)
	{
		if (UTextBlock* HelthText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Helth"))))
		{
			FString HealthString = FString::Printf(TEXT("HP : %.0f / %.0f"), CurrentHealth, MaxHealth);
			HelthText->SetText(FText::FromString(HealthString));
		}
	}
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
