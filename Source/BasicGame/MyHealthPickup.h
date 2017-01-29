// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableActor.h"
#include "MyHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class BASICGAME_API AMyHealthPickup : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	// constructor
	AMyHealthPickup();

	// overrides
	virtual void OnInteract_Implementation(AActor* Caller) override;

private:

	/** Heal amaount for pickup, editable in blueprints */
	UPROPERTY(EditDefaultsOnly)
	float HealAmount;
};
