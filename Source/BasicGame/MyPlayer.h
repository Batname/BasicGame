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

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

private:


};
