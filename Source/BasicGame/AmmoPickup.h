
#pragma once

#include "PickupBase.h"
#include "AmmoPickup.generated.h"

/**
 * Class for iteraction player with ammo
 */
UCLASS()
class BASICGAME_API AAmmoPickup : public APickupBase
{
	GENERATED_BODY()
	
public:
	// constructor
	AAmmoPickup();

	// overrides
	virtual void OnInteract_Implementation(AActor* Caller) override;

protected:

private:
	/** Keep in track pickup ammo amount */
	UPROPERTY(EditDefaultsOnly)
	int32 AmmoAmount;

	/** Store ammo type */
	UPROPERTY(EditDefaultsOnly)
	EAmmoType AmmoType;
	
};
