// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HTTP/HTTPRequestManager.h"
#include "Interfaces/IHttpRequest.h"
#include "UI/HTTP/HttpRequestTypes.h"
#include "UI/Interfaces/HUDManagement.h"
#include "UI/Portal/Interfaces/PortalManagement.h"
#include "PortalManager.generated.h"


/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UPortalManager : public UHTTPRequestManager, public IPortalManagement
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAPIStatusMessage SignUpStatusMessageDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FAPIStatusMessage ConfirmStatusMessageDelegate;

	UPROPERTY(BlueprintAssignable)
	FAPIStatusMessage SignInStatusMessageDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAPIRequestSucceeded OnSignUpSucceeded;

	UPROPERTY(BlueprintAssignable)
	FOnAPIRequestSucceeded OnConfirmSucceeded;

	UPROPERTY(BlueprintAssignable)
	FOnAPIRequestSucceeded OnSignInSucceeded;
	
	void SignIn(const FString& UserName, const FString& Password);
	void SignUp(const FString& UserName, const FString& Password, const FString& Email);
	void Confirm(const FString& ConfirmationCode);
	void SignOut(const FString& AccessToken);

	// IPortalManagement
	virtual void RefreshTokens(const FString& RefreshToken) override;

	UFUNCTION()
	void QuitGame();

	FDSSignUpResponse LastSignupResponse;
	FString LastUserName;

private:
	void SignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void Confirm_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SignIn_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void RefreshTokens_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SignOut_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
