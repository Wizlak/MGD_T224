// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MGGameInstance.generated.h"

#define MGSESSION_NAME FName(TEXT("MGSESSION"))

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// keyword that allows other classes to run this function
public:
	UMGGameInstance();
	
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();

	UFUNCTION(BlueprintPure, Category="Login")
	bool IsLoggedIn() const;

	UFUNCTION(BlueprintPure, Category="User")
	FString GetDisplayName() const;

	UFUNCTION(BlueprintPure, Category="Session")
	bool IsInSession() const;

	// host a game using EOS (LAN only)
	UFUNCTION(BlueprintCallable, Category="Session")
	void HostGame(bool lan = true);

	// find a hosted game and if found join the session
	UFUNCTION(BlueprintCallable, Category="Session")
	void FindAndJoinSession();

	// start a game if one exists
	UFUNCTION(BlueprintCallable, Category="Session")
	void StartLobbyGame();

	// runs when game ends
	UFUNCTION(BlueprintCallable, Category="Session")
	void EndGame();

	// keyword that only allows this class and derived/child classes to run this function
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success, const FString& error);

	UFUNCTION(BlueprintImplementableEvent, Category="Session")
	void OnSessionCreateComplete(bool success);

	UFUNCTION(BlueprintImplementableEvent, Category="Session")
	void OnSessionJoinComplete(bool success);
	
	// only this class can run private functions
private:
	// runs when EOS login completes
	void EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	// run when the create session function completes
	void SessionCreateComplete(FName SessionName, bool bWasSuccessful);

	// runs when a find session function completes
	void SessionFindComplete(bool bWasSuccessful);

	// runs on session join complete
	void SessionJoinComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// when find sessions is run, this will fill with found sessions
	TSharedPtr<FOnlineSessionSearch> FoundSessions;
};
