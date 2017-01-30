#pragma once

#include "GameFramework/Actor.h"
#include "BasicGame.h"
#include "PickupBase.generated.h"

UCLASS()
class BASICGAME_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	APickupBase();

	// Overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Funciton called when it interacted */
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	/** Mesh of this pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;

	/** Mesh of this pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

private:
	/** Keep in track status of interaction */
	UPROPERTY(EditDefaultsOnly)
	uint32 bTouchInteract : 1;
};
