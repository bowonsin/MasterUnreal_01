// Fill out your copyright notice in the Description page of Project Settings.


#include "SnadBoxWeaponBase.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TempGunActor.h"



void ASnadBoxWeaponBase::Fire()
{
	SandboxFire();
}

void ASnadBoxWeaponBase::Reload()
{
	CurrentAmmo = MaxAmmo;
	HandleFireDelay();
}

void ASnadBoxWeaponBase::LinetraceOneShot(FVector Direction)
{
	FHitResult Hit(ForceInit);

	FVector Start = FirePoint->GetComponentLocation();
	FVector End = Start + (Direction * Range);
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		{ this, GetOwner() },
		EDrawDebugTrace::ForDuration,
		Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f
	);

}

bool ASnadBoxWeaponBase::CheckAmmo()
{
	return AmmoPerFire <= CurrentAmmo;
}

void ASnadBoxWeaponBase::PlaySound(USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
}

void ASnadBoxWeaponBase::UpdateAmmo()
{
	CurrentAmmo = AmmoPerFire;
}