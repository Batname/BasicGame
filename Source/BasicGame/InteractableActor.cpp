#include "BasicGame.h"
#include "MyPlayer.h"
#include "InteractableActor.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default color
	Color = EStancilColor::SC_Blue;
}

// Define OnInteract instead OnInteract for reason it Will be overriden in blueprints
void AInteractableActor::OnInteract_Implementation(AActor * Caller)
{
	// Cast to MyPlayer, that is like dynamic_cast in std
	AMyPlayer* Player = Cast<AMyPlayer>(Caller);
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Now Interacting"));
		Destroy();
	}

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	// Fill mesh array for Actor
	for (UActorComponent* Mesh : GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* ThisMesh = Cast<UMeshComponent>(Mesh);
		if (ThisMesh)
		{
			Meshes.Push(ThisMesh);
		}
	}
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::OnBeginFocus()
{
	// check if player can interact
	if (!bCanInteract) return;

	// loop through meshes
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue((uint8)Color);
	}
}

void AInteractableActor::OnEndFocus()
{
	// loop through meshes
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

