// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "WeaponBase.generated.h"

/**
 * Base class for weapons
 */
UCLASS()
class BASICGAME_API AWeaponBase : public APickupBase
{
	GENERATED_BODY()
public:

	// Constructor
	AWeaponBase();

	/** Base function for add Ammo */
	void AddAmmo(int32 Amount);

protected:

private:
	
};
