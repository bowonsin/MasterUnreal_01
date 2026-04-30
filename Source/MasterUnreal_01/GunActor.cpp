// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	MaxAngle = 50.0f;
	MinAngle = 0.0f;

	ShootChecking = false;
	UpDownChecking = true;
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
	CurAngle = GetActorRotation().Pitch;
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ReboundGun(DeltaTime);
}

void AGunActor::ReboundGun(float DeltaTime)
{
	if (ShootChecking)
	{
		if (UpDownChecking)
		{
			if (CurAngle <= MaxAngle)
			{
				AddActorLocalRotation(FRotator(700.0f * DeltaTime, 0, 0));
				CurAngle = GetActorRotation().Pitch;
			}
			else
				UpDownChecking = false;
		}
		else
		{
			if (CurAngle >= MinAngle)
			{
				AddActorLocalRotation(FRotator(-50.0f * DeltaTime, 0, 0));
				CurAngle = GetActorRotation().Pitch;
			}
			else
			{
				ShootChecking = false;
				UpDownChecking = true;
			}
		}
		
	}
}

void AGunActor::ShootingGun()
{
	ShootChecking = true;
}

