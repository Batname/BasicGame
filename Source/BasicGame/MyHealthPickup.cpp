// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicGame.h"
#include "MyHealthPickup.h"
#include "MyPlayer.h"

AMyHealthPickup::AMyHealthPickup()
{
	// Set HealAmount
	HealAmount = 25.0f;
}

void AMyHealthPickup::OnInteract_Implementation(AActor* Caller)
{
	// Cast to player
	AMyPlayer* Player = Cast<AMyPlayer>(Caller);
	if (Player != nullptr) {
		Player->Heal(HealAmount);
		Destroy();
	}
}