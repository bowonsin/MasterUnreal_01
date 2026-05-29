// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"
// 필요 시 사용
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	LoadWithSoftPtr();
	
}

// Called every frame
void AMyTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTestActor::LoadWithSoftPtr()
{
	if (MySoftMesh.IsNull()) return;
	
	if (MySoftMesh.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("이미 로드됨, 메모리에서 즉시 참조하겠습니다."));
		MyOnLoadCompleted();
	}
	else
	{	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("메모리에 없음, 처음부터 로드를 실행합니다"));
		FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
		// 경로를 가져와주는 함수이다.
		Streamable.RequestAsyncLoad(MySoftMesh.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &AMyTestActor::MyOnLoadCompleted));
	}
}

void AMyTestActor::MyOnLoadCompleted()
{
	UStaticMesh* FinalMesh = MySoftMesh.Get();
	if (FinalMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("성공 : %s"), *FinalMesh->GetName()));
	}
}

