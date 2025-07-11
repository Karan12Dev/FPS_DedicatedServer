// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DSLocalPlayerSubsystem.h"
#include "UI/Portal/Interfaces/PortalManagement.h"


void UDSLocalPlayerSubsystem::InitializeTokens(const FAuthenticationResult& InAuthenticationResult, const TScriptInterface<IPortalManagement>& PortalManagement)
{
	AuthenticationResult = InAuthenticationResult;
	PortalManagementInterface = PortalManagement;
	SetRefreshTokenTimer();
}

void UDSLocalPlayerSubsystem::SetRefreshTokenTimer()
{
	UWorld* World = GetWorld();
	if (IsValid(World) && IsValid(PortalManagementInterface.GetObject()))
	{
		FTimerDelegate RefreshDelegate;
		RefreshDelegate.BindLambda([this](){ PortalManagementInterface->RefreshTokens(AuthenticationResult.RefreshToken); });
		World->GetTimerManager().SetTimer(RefreshTimer, RefreshDelegate, TokenRefreshInterval, false);
	}
}

void UDSLocalPlayerSubsystem::UpdateTokens(const FString& AccessToken, const FString& IdToken)
{
	AuthenticationResult.AccessToken = AccessToken;
	AuthenticationResult.IdToken = IdToken;
	AuthenticationResult.Dump();
	SetRefreshTokenTimer();
}

FAuthenticationResult UDSLocalPlayerSubsystem::GetAuthResult() const
{
	return AuthenticationResult;
}
