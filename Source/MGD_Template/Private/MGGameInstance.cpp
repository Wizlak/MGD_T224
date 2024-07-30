// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UMGGameInstance::LoginEOS()
{
	// this is the online subsystem
	// this gives us access to all of the online subsystem functions
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	// if the ossRef returns null
	// exit the function
	if (!ossRef)
		return;

	// this is the identity interface for the EOS
	// we can get info about the player's account for this interface
	// it also allows us to access authentication (login / logout)
	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	// if the identityRef returns null
	// exit the function
	if (!identityRef)
		return;

	// this sets up the type of account credentials that the login will expect
	// the account portal is a login portal that opens when you try to login
	FOnlineAccountCredentials accCreds;
	accCreds.Id = FString();
	accCreds.Token = FString();
	accCreds.Type = FString(TEXT("accountportal"));

	// run the login portal
	identityRef->Login(0, accCreds);
}
