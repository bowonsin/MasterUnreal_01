// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


// 1대 다수로 블루프린트 까지 지원하는 죽었을 떄
// 델리게이트 이름은 F부터 시작한다
// 2번쨰는 유형이고 마지막은 이름이다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature,AController* ,Instiagtor);
// 데미지를 입었을 때 
// 새로운 HP, 현제 HP, 바뀌는 HP 넣기
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature,float, NewHealth ,float, MaxHealth,float, HealthChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERUNREAL_01_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// UActorComponent F12로 타고 들어가서 TickComponent를 검색해서 긇어 와야한다.
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)override;
	// Sets default values for this component's properties
	UMyActorComponent();
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthDeadSignature OnHealthDead;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthDamagedSignature OnHealthDamaged;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Health")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
	UPROPERTY()
	UUserWidget* HUDWidgetInstance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentHealth;
private:
	
	UFUNCTION()
	void DamageTake(AActor* DamageActor, float Damage, const UDamageType* DamageType,AController* Instigator,AActor* Cuaser );
};
