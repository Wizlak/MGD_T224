// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGDCharacter.generated.h"

UCLASS()
class MGD_TEMPLATE_API AMGDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMGDCharacter();

	// Move the character based on an axis
	UFUNCTION(BlueprintCallable, Category="Movement")
	void Pure_MoveCharacter(const FVector2D Axis);

	// Rotate the character controller based on axis
	UFUNCTION(BlueprintCallable, Category="Controller")
	void Pure_RotateController(const FVector2D Axis);

protected:
	UFUNCTION(Server, Reliable, Category="Replication")
	void Server_RepPitch(const float& Pitch);

	UFUNCTION(NetMulticast, Reliable, Category="Replication")
	void Multi_RepPitch(const float& Pitch);

public:
	// Move axis of the character
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector2D pMoveAxis;

	// Replicated pitch for the character		
	UPROPERTY(BlueprintReadOnly, Category="Pitch")
	float pRepPitch;
};
