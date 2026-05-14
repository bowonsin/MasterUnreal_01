// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Cloth.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

AItem_Cloth::AItem_Cloth()
{
}

void AItem_Cloth::OnFireDected_Implementation(float Temperature, FVector HitLocation)
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
}
