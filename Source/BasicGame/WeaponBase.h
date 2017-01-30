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

	// Overrides
	virtual void OnInteract_Implementation(AActor* Caller) override;

	/** Base function for add Ammo */
	UFUNCTION()
	void AddAmmo(int32 Amount);

	/** Base funciton for make damage */
	UFUNCTION()
	void DealDamage();

	/** Base funciton for weapon fire */
	UFUNCTION()
	void Fire();

	/** Show animation during fire */
	UFUNCTION()
	void SpawnFireEffect();

	/** Show animation for spawn impact */
	UFUNCTION()
	void SpawnImpactEffect();

	/** Calculate spread */
	UFUNCTION()
	FVector CalcSpread();

	/** Switch to another owner */
	UFUNCTION()
	void ChangeOwner(AActor* NewOwner);

protected:

	/** Keep in track wepon mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

private:
	/** Owning player */
	UPROPERTY()
	class AMyPlayer* OwningPlayer;

	/** Weapon type enum */
	UPROPERTY(EditDefaultsOnly)
	EAmmoType AmmoType;

	/** Keep in track max ammo amount*/
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	/** Keep in track current ammont*/
	UPROPERTY()
	int32 CurrentAmmo;

	/** Spread fo weapon */
	UPROPERTY(EditDefaultsOnly)
	float Spread;

	/** Base damage for weapon */
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage;

	/** Bool for uses */
	UPROPERTY(EditDefaultsOnly)
	uint32 bUsesProjectile : 1;

	/** Class fointer for any cllases dirives from, if bUsesProjectile == false, we can notedit this property */
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bUsesProjectile"))
	TSubclassOf<class AProjectileBase> Projectile;
};
