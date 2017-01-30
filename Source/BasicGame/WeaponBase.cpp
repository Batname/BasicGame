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
	//TODO
}

void AWeaponBase::Fire()
{
	//TODO
}

void AWeaponBase::SpawnFireEffect()
{
	//TODO
}

void AWeaponBase::SpawnImpactEffect()
{
	//TODO
}

FVector AWeaponBase::CalcSpread()
{
	if (OwningPlayer != nullptr)
	{
		FVector Direction = OwningPlayer->GetActorRotation().Vector();

		// Convert from radians to degrees, basicly that is sin for angle
		// atan = arcus tangens -> for convertation to Angle in degrees
		float Angle = atan(Spread / 10000);

		// Return random point for angle
		return FMath::VRandCone(Direction, Angle);
	}
	else 
	{
		FVector Direction = GetActorRotation().Vector();
		float Angle = atan(Spread / 10000);
		return FMath::VRandCone(Direction, Angle);
	}
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
