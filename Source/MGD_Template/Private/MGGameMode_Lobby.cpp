// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameMode_Lobby.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMGGameMode_Lobby::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	// Initialise an empty local array of player starts
	TArray<AActor*> playerStartArray;

	// Get all of the player starts and add them into the playerStartArray variable
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStartArray);

	// if there are no player starts stop the function
	if(playerStartArray.IsEmpty())
		return;

	// looping through all of the actors in the array
	for (AActor* actorRef : playerStartArray)
	{
		// testing to make sure the actor is a player start
		if (APlayerStart* psRef = Cast<APlayerStart>(actorRef))
		{
			// assigning an index depending on the tag of the player start
			int playerStartIndex = 1;

			// assigning the index if it equals any of the following
			if (psRef->PlayerStartTag == FName('Player2'))
				playerStartIndex = 2;
			else if (psRef->PlayerStartTag == FName('Player3'))
				playerStartIndex = 3;
			else if (psRef->PlayerStartTag == FName('Player4'))
				playerStartIndex = 4;
			else if (psRef->PlayerStartTag == FName('Player5'))
				playerStartIndex = 5;
			else if (psRef->PlayerStartTag == FName('Player6'))
				playerStartIndex = 6;

			// getting the number of players in the game
			const int32 numPlayers = UGameplayStatics::GetNumPlayerStates(GetWorld());

			// checking if the player start tag matches this player
			if (playerStartIndex == numPlayers)
			{
				// restart the player and add it to the correct player start
				RestartPlayerAtPlayerStart(NewPlayer, psRef);
				break;
			}
		}	
	}
}
