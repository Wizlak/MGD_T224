// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// keyword that allows other classes to run this function
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();

	UFUNCTION(BlueprintPure, Category="Login")
	bool IsLoggedIn() const;

	UFUNCTION(BlueprintPure, Category="User")
	FString GetDisplayName() const;

	// keyword that only allows this class and derived/child classes to run this function
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success, const FString& error);
	
	// only this class can run private functions
private:
	// runs when EOS login completes
	void EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	
};
