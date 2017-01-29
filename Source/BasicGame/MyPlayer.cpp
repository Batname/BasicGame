
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

	// Set Health points
	MaxHealthPoints = 100.0f;
	HealthPoints = MaxHealthPoints;

	// Create Camera Player object and add test for blueprints
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	// Create Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	// Attach camera
	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);

	// Set player movements
	WalkSpeed = 600.0f;
	RunSpeed = 1200.0f;
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
		GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("HP: %f"), HealthPoints));
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
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::StopRun);
}

void AMyPlayer::MoveForward(float Val)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	//FVector Forvard = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	FVector Forvard(1, 0, 0);
	AddMovementInput(Forvard, Val);
}

void AMyPlayer::MoveRight(float Val)
{
	FRotator Rotation(0, GetActorRotation().Yaw, 0);
	//FVector Right = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	FVector Right(0, 1, 0);
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

void AMyPlayer::StartRun()
{
	// Set run speed and movement status
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyPlayer::StopRun()
{
	// Set walk speed and movement status
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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

float AMyPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Get calculation result of damage from parent
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HealthPoints = HealthPoints - ActualDamage;

	// Check if player still has HP
	if (HealthPoints <= 0) OnDeath();

	return ActualDamage;
}

void AMyPlayer::OnDeath()
{
	Destroy();
	GEngine->AddOnScreenDebugMessage(0, 1000.0f, FColor::Red, FString::Printf(TEXT("You Have died!")));
}

void AMyPlayer::Heal(float Amount)
{
	if (Amount > 0)
	{
		HealthPoints += Amount;
	}
}