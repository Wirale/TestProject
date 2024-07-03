// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "BPFLs/HelperBPFL.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

AFP_FirstPersonCharacter::AFP_FirstPersonCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}


void AFP_FirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_FirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_FirstPersonCharacter::MoveRight);
	
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFP_FirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFP_FirstPersonCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("SpawnBuildingSource", IE_Pressed, this, &AFP_FirstPersonCharacter::SpawnBuildingSource);
	PlayerInputComponent->BindAction("SpawnBuildingTransmitter", IE_Pressed, this, &AFP_FirstPersonCharacter::SpawnBuildingTransmitter);
	PlayerInputComponent->BindAction("SpawnBuildingPortal", IE_Pressed, this, &AFP_FirstPersonCharacter::SpawnBuildingPortal);

	PlayerInputComponent->BindAction("OpenNextLevel", IE_Pressed, this, &AFP_FirstPersonCharacter::OpenNextLevel);
	PlayerInputComponent->BindAction("OpenPreviewLevel", IE_Pressed, this, &AFP_FirstPersonCharacter::OpenPreviewLevel);
}

void AFP_FirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFP_FirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFP_FirstPersonCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFP_FirstPersonCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFP_FirstPersonCharacter::SpawnBuildingSource()
{
	UHelperBPFL::SpawnBuildingByType(this, Building_Source);
}

void AFP_FirstPersonCharacter::SpawnBuildingTransmitter()
{
	UHelperBPFL::SpawnBuildingByType(this, Building_Transmitter);
}

void AFP_FirstPersonCharacter::SpawnBuildingPortal()
{
	UHelperBPFL::SpawnBuildingByType(this, Building_Portal);
}

void AFP_FirstPersonCharacter::OpenNextLevel()
{
	UHelperBPFL::OpenNewLevelByDirection(this, RIGHT);
}

void AFP_FirstPersonCharacter::OpenPreviewLevel()
{
	UHelperBPFL::OpenNewLevelByDirection(this, LEFT);
}
