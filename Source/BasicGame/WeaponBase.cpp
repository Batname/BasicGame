// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicGame.h"
#include "WeaponBase.h"
#include "MyPlayer.h"

AWeaponBase::AWeaponBase()
{
}

void AWeaponBase::OnInteract_Implementation(AActor * Caller)
{
	// Cast and check MyPlayer
	AMyPlayer* Player = Cast<AMyPlayer>(Caller);
	if (Player == nullptr) return;

	// Add this weapon to Player
	Player->AddToInventory(this);
}

void AWeaponBase::AddAmmo(int32 Amount)
{
	// Increase ammo, but it will be less thenmax ammo
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, CurrentAmmo, MaxAmmo);
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

void AWeaponBase::ChangeOwner(AActor* NewOwner)
{
	// Cast and check MyPlayer
	AMyPlayer* Player = Cast<AMyPlayer>(NewOwner);
	if (Player == nullptr) return;

	OwningPlayer = Player;

	// Set the owner of this Actor
	SetOwner(OwningPlayer);
}
