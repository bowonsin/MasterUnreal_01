// Fill out your copyright notice in the Description page of Project Settings.


#include "TempGunActor.h"


ATempGunActor::ATempGunActor()
{
	
}
void ATempGunActor::Fire()
{
	if (!CanFire) return;
	if (CheckAmmo())
	{
		// 순서는 여기서 마음대로 

		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		
		Super::Fire();

		return;
	}
}
bool ATempGunActor::CheckAmmo_Implementation()
{
	return AmmoPerFire <= CurrentAmmo;
}
void ATempGunActor::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;

}

void ATempGunActor::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;

}
