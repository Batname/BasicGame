
#include "BasicGame.h"
#include "AmmoPickup.h"
#include "MyPlayer.h"

AAmmoPickup::AAmmoPickup()
{

}

void AAmmoPickup::OnInteract_Implementation(AActor* Caller)
{
	// Cast and check player
	AMyPlayer* Player = Cast<AMyPlayer>(Caller);
	if (Player != nullptr)
	{
		 Player->AddAmmo(AmmoAmount, AmmoType);
	}
}
