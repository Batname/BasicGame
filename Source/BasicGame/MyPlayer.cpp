
#include "BasicGame.h"
#include "MyPlayer.h"


AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

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
}

