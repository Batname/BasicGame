// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IteractableActor.generated.h"

UCLASS()
class BASICGAME_API AIteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIteractableActor();

	/** OnInteract function will be overriden in blueprints, because BlueprintNative event means it can be overriden in blueprints
	* @param Caller Instance of AActor
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Category=Interaction)
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Action will be called when actor focused */
	UFUNCTION()
	void OnBeginFocus();

	/** Action will be called when actor un focused */
	UFUNCTION()
	void OnEndFocus();
	
private:
	/** Boolean for posobility interaction */
	UPROPERTY(VisibleAnywhere, Category = "InteractableActor")
	uint32 bCanInteract : 1;

	/** collection of meshes */
	UPROPERTY(VisibleAnywhere, Category = "InteractableActor")
	TArray<class UMeshComponent*> Meshes;

	/** Set Stancil Color */
	UPROPERTY(VisibleAnywhere, Category = "InteractableActor")
	EStancilColor Color;
};
