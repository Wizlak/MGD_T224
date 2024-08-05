// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDCharacter.h"

// Sets default values
AMGDCharacter::AMGDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pRepPitch = 0.0f;
}

void AMGDCharacter::Pure_MoveCharacter(const FVector2D Axis)
{
	// Update the member axis
	pMoveAxis = Axis;

	// Move character based on Y axis
	AddMovementInput(GetActorRotation().Vector(), Axis.Y);

	//Move character based on X axis
	AddMovementInput(FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y), Axis.X);
}

void AMGDCharacter::Pure_RotateController(const FVector2D Axis)
{
	// Rotate the controller yaw based on X axis
	AddControllerYawInput(Axis.X);

	// Rotate the controller pitch based on Y axis
	AddControllerPitchInput(-Axis.Y);

	// Is the pRepPitch 10 units difference from the controller's pitch
	if (FMath::Abs(pRepPitch - GetControlRotation().Pitch) > 10.0f)
	{
		// Are we the server
		if (HasAuthority())
		{
			Multi_RepPitch(GetControlRotation().Pitch);
		}
		else
		{
			Server_RepPitch(GetControlRotation().Pitch);
		}
	}
		
}

void AMGDCharacter::Server_RepPitch_Implementation(const float& Pitch)
{
	// Run the multicast to update all of the clients
	Multi_RepPitch(Pitch);
}

void AMGDCharacter::Multi_RepPitch_Implementation(const float& Pitch)
{
	// Update the pitch to match the value
	pRepPitch=Pitch;
}

