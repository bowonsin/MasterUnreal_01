// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TestDamageType.h"


// Sets default values
AStudyActor::AStudyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudyActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AStudyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStudyActor::StartSingleTrace()
{
	TArray<FHitResult> HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	UKismetSystemLibrary::LineTraceMulti
	(
		GetWorld()
		, GetActorLocation()
		, GetActorForwardVector() * 1000.0f + GetActorLocation()
		, UEngineTypes::ConvertToTraceType(ECC_Visibility) // 안정성 때문에 사용한다
		, false // false 면 단순콜리전 , true 면 복합 콜리전
		, ActorsToIgnore
		, EDrawDebugTrace::ForOneFrame //EDrawDebugTrace 은 Enum 이다.
		, HitResult
		, true
		, FLinearColor::Red // 안맞으면 빨간색
		, FLinearColor::Green // 맞으면 초록색
	);
	/*
	* 싱글 트레이스 용
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld()
		, GetActorLocation()
		, GetActorForwardVector() * 1000.0f + GetActorLocation()
		, UEngineTypes::ConvertToTraceType(ECC_Visibility) // 안정성 때문에 사용한다
		, false // false 면 단순콜리전 , true 면 복합 콜리전
		, ActorsToIgnore
		, EDrawDebugTrace::ForOneFrame //EDrawDebugTrace 은 Enum 이다.
		, HitResult
		, true
		, FLinearColor::Red // 안맞으면 빨간색
		, FLinearColor::Green // 맞으면 초록색
	);
	*/

}

// UWorld
void AStudyActor::StartAsyncTarce()
{
	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &AStudyActor::OnAsyncTraceCompleted);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.WorldDynamic = ECR_Block;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;

	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Multi,
		GetActorLocation(),
		GetActorForwardVector() * 1000.f + GetActorLocation(),
		ECC_Visibility,
		QueryParams,
		ResponseParams,
		&TraceDelegate
	);



}

void AStudyActor::OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
	for (const FHitResult& Hit : Data.OutHits)

	{
		AActor* HitActor = Hit.GetActor();

		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Multi Hit Actor : %s"), *HitActor->GetName()));

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20.f, 12, FColor::Green, false, 2.f);

		UGameplayStatics::ApplyPointDamage
		(
			HitActor
			,50.0f
			,GetActorForwardVector()
			,Hit
			,GetInstigatorController()
			,this
			,UTestDamageType::StaticClass()

		);

	}
}

