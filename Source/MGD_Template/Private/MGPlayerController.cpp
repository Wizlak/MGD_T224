// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerController.h"

void AMGPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	UE_LOG(LogTemp, Warning, TEXT("On possess"))

	Pure_OnRepPossess(GetPawn());
}

void AMGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (HasAuthority())
		Pure_OnRepPossess(InPawn);
}
