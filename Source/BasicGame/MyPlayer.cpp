
#include "BasicGame.h"
#include "MyPlayer.h"
#include "InteractableActor.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set interaction distance
	InteractionDistance = 300.0f;

	// Set trace params
	TraceParams = FCollisionQueryParams(FName(TEXT("TraceParams")), false, this);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Controller && Controller->IsLocalController())
	{
		HandleHighlight();
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input to payer from project setting editor
	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);
	InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);
}

void AMyPlayer::MoveForward(float Val)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	FVector Forvard = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Forvard, Val);
}

void AMyPlayer::MoveRight(float Val)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	FVector Right = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Right, Val);
}

void AMyPlayer::LookYaw(float Val)
{
	AddControllerYawInput(Val);
}

void AMyPlayer::LookPitch(float Val)
{
	AddControllerPitchInput(Val);
}

void AMyPlayer::Use()
{
	AInteractableActor* Interactable = FindFocusedActor();
	if (Interactable)
	{
		Interactable->OnInteract(this);
	}
}

AInteractableActor* AMyPlayer::FindFocusedActor()
{
	// If no controller return from function
	if (!Controller) return nullptr;

	FVector Location;
	FRotator Rotation;
	FHitResult Hit(ForceInit);
	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * InteractionDistance);

	// Make math for Line trace for check view collision
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);
	if (Hit.bBlockingHit)
	{
		// Cast ans return
		AInteractableActor* MyCastActor = Cast<AInteractableActor>(Hit.GetActor());
		if (MyCastActor != nullptr) return MyCastActor;

	}

	return nullptr;
}

void AMyPlayer::HandleHighlight()
{
	AInteractableActor* NewHighlight = FindFocusedActor();
	if (NewHighlight != nullptr)
	{
		// If it not same focused object
		if (NewHighlight != FocusedActor)
		{
			// swith focused actors
			if (FocusedActor != nullptr) FocusedActor->OnEndFocus();
			NewHighlight->OnBeginFocus();
			FocusedActor = NewHighlight;
		}
	}
	else
	{
		if (FocusedActor != nullptr) FocusedActor->OnEndFocus();
		FocusedActor = nullptr;
	}
}

