// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignInOverlay.generated.h"

class UWidgetSwitcher;
class UButton;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API USignInOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPortalManager> PortalManagerClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;
	

protected:
	virtual void NativeConstruct() override;
	
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class USignInPage> SignInPage;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class USignUpPage> SignUpPage;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UConfirmSignUpPage> ConfirmSignUpPage;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class USuccessConfirmedPage> SuccessConfirmedPage;
	
	UPROPERTY()
	TObjectPtr<UPortalManager> PortalManager;

	UFUNCTION()
	void ShowSignInPage();

	UFUNCTION()
	void ShowSignUpPage();

	UFUNCTION()
	void ShowConfirmSignUpPage();

	UFUNCTION()
	void ShowSuccessConfirmedPage();

	UFUNCTION()
	void SignInButtonClicked();

	UFUNCTION()
	void SignUpButtonClicked();

	UFUNCTION()
	void ConfirmButtonClicked();

	UFUNCTION()
	void OnSignUpSucceeded();

	UFUNCTION()
	void OnConfirmSucceded();

	UFUNCTION()
	void OnSignInSucceeded();

	void AutoSignIn();
};
