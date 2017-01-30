// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicGame.h"
#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
}

void AWeaponBase::OnInteract_Implementation(AActor * Caller)
{
}

void AWeaponBase::AddAmmo(int32 Amount)
{
	// @TODO
}

void AWeaponBase::DealDamage()
{
}

void AWeaponBase::Fire()
{
}

void AWeaponBase::SpawnFireEffect()
{
}

void AWeaponBase::SpawnImpactEffect()
{
}

FVector AWeaponBase::CalcSpread()
{
	return FVector();
}

void AWeaponBase::ChangeOwner(AActor * NewOwner)
{
}
