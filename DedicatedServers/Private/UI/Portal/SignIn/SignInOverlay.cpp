// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignInOverlay.h"
#include "UI/Portal/PortalManager.h"
#include "UI/Portal/SignIn/SignInPage.h"
#include "UI/Portal/SignIn/SignUpPage.h"
#include "UI/Portal/SignIn/ConfirmSignUpPage.h"
#include "UI/Portal/SignIn/SuccessConfirmedPage.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Player/DSLocalPlayerSubsystem.h"


void USignInOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	check(PortalManagerClass);
	
	PortalManager = NewObject<UPortalManager>(this, PortalManagerClass);

	SignInPage->Button_SignIn->OnClicked.AddDynamic(this, &USignInOverlay::SignInButtonClicked);
	SignInPage->Button_SignUp->OnClicked.AddDynamic(this, &USignInOverlay::ShowSignUpPage);
	SignInPage->Button_Quit->OnClicked.AddDynamic(PortalManager, &UPortalManager::QuitGame);
	PortalManager->OnSignInSucceeded.AddDynamic(this, &USignInOverlay::OnSignInSucceeded);
	PortalManager->SignInStatusMessageDelegate.AddDynamic(SignInPage, &USignInPage::UpdateStatusMessage);

	SignUpPage->Button_Back->OnClicked.AddDynamic(this, &USignInOverlay::ShowSignInPage);
	SignUpPage->Button_SignUp->OnClicked.AddDynamic(this, &USignInOverlay::SignUpButtonClicked);
	PortalManager->OnSignUpSucceeded.AddDynamic(this, &USignInOverlay::OnSignUpSucceeded);
	PortalManager->SignUpStatusMessageDelegate.AddDynamic(SignUpPage, &USignUpPage::UpdateStatusMessage);

	ConfirmSignUpPage->Button_Confirm->OnClicked.AddDynamic(this, &USignInOverlay::ConfirmButtonClicked);
	ConfirmSignUpPage->Button_Back->OnClicked.AddDynamic(this, &USignInOverlay::ShowSignUpPage);
	PortalManager->OnConfirmSucceeded.AddDynamic(this, &USignInOverlay::OnConfirmSucceded);
	PortalManager->ConfirmStatusMessageDelegate.AddDynamic(ConfirmSignUpPage, &UConfirmSignUpPage::UpdateStatusMessage);

	SuccessConfirmedPage->Button_Ok->OnClicked.AddDynamic(this, &USignInOverlay::ShowSignInPage);

	ShowSignInPage();
	AutoSignIn();
}

void USignInOverlay::ShowSignInPage()
{
	if (IsValid(WidgetSwitcher) && IsValid(SignInPage))
	{
		WidgetSwitcher->SetActiveWidget(SignInPage);
	}
}

void USignInOverlay::ShowSignUpPage()
{
	if(IsValid(WidgetSwitcher) && IsValid(SignUpPage))
	{
		WidgetSwitcher->SetActiveWidget(SignUpPage);
	}
}

void USignInOverlay::ShowConfirmSignUpPage()
{
	if (IsValid(WidgetSwitcher) && IsValid(ConfirmSignUpPage))
	{
		WidgetSwitcher->SetActiveWidget(ConfirmSignUpPage);
	}
}

void USignInOverlay::ShowSuccessConfirmedPage()
{
	if (IsValid(WidgetSwitcher) && IsValid(SuccessConfirmedPage))
	{
		WidgetSwitcher->SetActiveWidget(SuccessConfirmedPage);
	}
}

void USignInOverlay::SignInButtonClicked()
{
	SignInPage->Button_SignIn->SetIsEnabled(false);
	const FString Username = SignInPage->TextBox_UserName->GetText().ToString();
	const FString Password = SignInPage->TextBox_Password->GetText().ToString();
	if (UDSLocalPlayerSubsystem* DSLocalPlayerSubsystem = PortalManager->GetDSLocalPlayerSubsystem(); IsValid(DSLocalPlayerSubsystem))
	{
		DSLocalPlayerSubsystem->Password = Password;
	}
	if (IsValid(PortalManager))
	{
		PortalManager->SignIn(Username, Password);
	}
}

void USignInOverlay::SignUpButtonClicked()
{
	const FString Username = SignUpPage->TextBox_UserName->GetText().ToString();
	const FString Password = SignUpPage->TextBox_Password->GetText().ToString();
	const FString ConfirmPassword = SignUpPage->TextBox_ConfirmPassword->GetText().ToString();
	const FString Email = SignUpPage->TextBox_Email->GetText().ToString();
	SignUpPage->Button_SignUp->SetIsEnabled(false);
	if (IsValid(PortalManager))
	{
		PortalManager->SignUp(Username, Password, Email);
	}
}

void USignInOverlay::ConfirmButtonClicked()
{
	const FString Code = ConfirmSignUpPage->TextBox_ConfirmationCode->GetText().ToString();
	ConfirmSignUpPage->Button_Confirm->SetIsEnabled(false);
	if (IsValid(PortalManager))
	{
		PortalManager->Confirm(Code);
	}
}

void USignInOverlay::OnSignUpSucceeded()
{
	SignUpPage->ClearTextBoxes();
	ConfirmSignUpPage->TextBlock_Destination->SetText(FText::FromString(PortalManager->LastSignupResponse.CodeDeliveryDetails.Destination));
	ShowConfirmSignUpPage();
}

void USignInOverlay::OnConfirmSucceded()
{
	ConfirmSignUpPage->ClearTextBoxes();
	ShowSuccessConfirmedPage();
}

void USignInOverlay::OnSignInSucceeded()
{
	SignInPage->ClearTextBoxes();
}

void USignInOverlay::AutoSignIn()
{
	if (UDSLocalPlayerSubsystem* DSLocalPlayerSubsystem = PortalManager->GetDSLocalPlayerSubsystem(); IsValid(DSLocalPlayerSubsystem))
	{
		const FString& Username = DSLocalPlayerSubsystem->Username;
		const FString& Password = DSLocalPlayerSubsystem->Password;
		if (Username.IsEmpty() || Password.IsEmpty()) return;
		SignInPage->Button_SignIn->SetIsEnabled(false);
		PortalManager->SignIn(Username, Password);
	}
}
