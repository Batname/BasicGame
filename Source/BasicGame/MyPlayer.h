// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
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
	UFUNCTION(BlueprintCallable, Category = "MyPlayerInput")
	void MoveForward(float Val);

	/** Move right player keybord input*/
	UFUNCTION(BlueprintCallable, Category = "MyPlayerInput")
	void MoveRight(float Val);

	/** Look yaw player mouse input*/
	UFUNCTION(BlueprintCallable, Category = "MyPlayerInput")
	void LookYaw(float Val);

	/** Look pitch player mouse input*/
	UFUNCTION(BlueprintCallable, Category = "MyPlayerInput")
	void LookPitch(float Val);

	/** Player use keybord action*/
	UFUNCTION(BlueprintCallable, Category = "MyPlayerInput")
	void Use();

	/** Forward definition because we cannot include one header file inside onother */
	UFUNCTION(BlueprintPure, Category = "MyPlayer")
	class AInteractableActor* FindFocusedActor();
	
	/** Set action for highliting */
	UFUNCTION(BlueprintCallable, Category = "MyPlayer")
	void HandleHighlight();

	/** Action on death */
	UFUNCTION(BlueprintCallable, Category = "MyPlayer")
	void OnDeath();

	/** Set new health points */
	UFUNCTION()
	void Heal(float Amount);
	
private:

	/** Set distanse for player interaction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyPlayer", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance;

	/** Keep in track MAX player Health Points */
	UPROPERTY(EditDefaultsOnly)
	float MaxHealthPoints;

	/** Keep in track player Health Points */
	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess = "true"), Category=Health)
	float HealthPoints;

	/** Keep in track focused actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPlayer", meta = (AllowPrivateAccess = "true"))
	AInteractableActor* FocusedActor;

	/** Trace params property */
	FCollisionQueryParams TraceParams;
};
