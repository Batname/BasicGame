#include "BasicGame.h"
#include "PickupBase.h"


APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create object instances
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

	// Assign root component
	RootComponent = CollisionSphere;
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");
	PickupMesh->SetupAttachment(RootComponent);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// set class default interact status
	//bTouchInteract = true;
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	if (bTouchInteract)
	{
		// Dynamic multi-cast delegate
		// @TODO Potential error Add instead AddDynamic
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnBeginOverlap);
	}
	
}
void APickupBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickupBase::OnInteract_Implementation(AActor * Caller)
{
}

void APickupBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnInteract(OtherActor);
}

