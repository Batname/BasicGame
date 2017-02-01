
#include "BasicGame.h"
#include "MyPlayer.h"
#include "AssaultRifleBase.h"
#include "LaserRifleBase.h"
#include "RocketLaucherBase.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set MAX Health points
	MaxHealthPoints = 100.0f;

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

	// Set player HP
	HealthPoints = MaxHealthPoints;

	// Call Blueprint update health funciton
	HUDUpdateHP();
}

void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Controller && Controller->IsLocalController())
	{
		// Cast player controller
		APlayerController* PC = Cast<APlayerController>(Controller);
		if (PC != nullptr)
		{
			FVector MouseLocation, MouseDirection; // It will be passed to function as referance
			
			// Set mouse location and direction
			PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
			
			// Set actor rotation according to mouse direction
			SetActorRotation(FRotator(0, MouseDirection.Rotation().Yaw, 0));
		}
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input to payer from project setting editor
	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::StopRun);
}

void AMyPlayer::MoveForward(float Val)
{
	FVector Forvard(1, 0, 0);
	AddMovementInput(Forvard, Val);
}

void AMyPlayer::MoveRight(float Val)
{
	FVector Right(0, 1, 0);
	AddMovementInput(Right, Val);
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

float AMyPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Get calculation result of damage from parent
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HealthPoints = HealthPoints - ActualDamage;

	// Call Blueprint update health funciton
	HUDUpdateHP();

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

		// Call Blueprint update health funciton
		HUDUpdateHP();
	}
}

void AMyPlayer::AddAmmo(int32 Amount, EAmmoType AmmoType)
{
	// define wepon type and add amount
	switch (AmmoType)
	{
	case EAmmoType::AT_Bullets:
		if (Inventory.AssaultRifle != nullptr)
		{
			Inventory.AssaultRifle->AddAmmo(Amount);
		}
		break;
	case EAmmoType::AT_Rockets:
		if (Inventory.RocketLaucher != nullptr)
		{
			Inventory.RocketLaucher->AddAmmo(Amount);
		}
		break;
	case EAmmoType::AT_Lasers:
		if (Inventory.LaserRifle != nullptr)
		{
			Inventory.LaserRifle->AddAmmo(Amount);
		}
		break;
	default:
		break;
	}
}

void AMyPlayer::AddToInventory(AWeaponBase * NewWeapon)
{
}
