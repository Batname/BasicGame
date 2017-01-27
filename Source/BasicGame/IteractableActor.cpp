// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicGame.h"
#include "IteractableActor.h"


// Sets default values
AIteractableActor::AIteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIteractableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

