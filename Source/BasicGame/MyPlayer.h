// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BasicGame.h"
#include "MyPlayer.generated.h"

UCLASS()
class BASICGAME_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	AMyPlayer();

	// overrides
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/** Move forward player keybord input*/
	UFUNCTION(BlueprintCallable, Category = PlayerControl)
	void MoveForward(float Val);

	/** Move right player keybord input*/
	UFUNCTION(BlueprintCallable, Category = PlayerControl)
	void MoveRight(float Val);

	/** Start running */
	UFUNCTION(BlueprintCallable, Category = PlayerControl)
	void StartRun();

	/** Stop running */
	UFUNCTION(BlueprintCallable, Category = PlayerControl)
	void StopRun();

	/** Action on death */
	UFUNCTION(BlueprintCallable, Category = "MyPlayer")
	void OnDeath();

	/** Set new health points */
	UFUNCTION()
	void Heal(float Amount);

	/** Add ammo to player */
	UFUNCTION()
	void AddAmmo(int32 Amount, EAmmoType AmmoType);

	/** Add inventory to player */
	UFUNCTION()
	void AddToInventory(class AWeaponBase* NewWeapon);

	// HUD
	/** Updating player HP for blueprints calls */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HUD)
	void HUDUpdateHP();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

private:

	/** Keep in track MAX player Health Points */
	UPROPERTY(EditDefaultsOnly)
	float MaxHealthPoints;

	/** Player walk speed */
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed;

	/** Player run speed */
	UPROPERTY(EditDefaultsOnly)
	float RunSpeed;

	/** Keep in track status of player movement. 1 byte Bool value */
	UPROPERTY(EditDefaultsOnly)
	uint32 bIsRunning : 1;

	/** Player inventory */
	UPROPERTY()
	FPlayerInventory Inventory;

	/** Keep in track player Health Points */
	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess = "true"), Category=Health)
	float HealthPoints;

};
