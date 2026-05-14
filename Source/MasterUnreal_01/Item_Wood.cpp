// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Wood.h"

#include "Kismet/GameplayStatics.h" // 스폰 함수 사용을 위해 필수 
#include "Particles/ParticleSystem.h" // 파티클 시스템 헤더
AItem_Wood::AItem_Wood()
{
}

void AItem_Wood::OnFireDected_Implementation(float Temperature, FVector HitLocation)
{
	if (FireEffects)
	{
		//특정 월드 좌표에 파티클 시스템(이펙트)을 생성하고 즉시 실행
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld() 
			,FireEffects
			,GetActorLocation()// this 좌표
			,GetActorRotation() // this 회전
			,FVector(1.f)
			);
	}
		
		/*
		UGameplayStatics::SpawnEmitterAtLocation(
	GetWorld(),            // 1. 월드 컨텍스트
	ParticleSystem,        // 2. 생성할 파티클 에셋 (UParticleSystem*)
	SpawnLocation,         // 3. 생성될 위치 (FVector)
	SpawnRotation,         // 4. 생성될 회전 값 (FRotator)
	FVector(1.0f),         // 5. 스케일 (기본값 1.0)
	true                   // 6. 자동 파괴 여부 (기본값 true)
	*/
}
