// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignInPage.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"


void USignInPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidget)
{
	TextBlock_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidget)
	{
		Button_SignIn->SetIsEnabled(true);
	}
}

void USignInPage::ClearTextBoxes()
{
	TextBox_UserName->SetText(FText::GetEmpty());
	TextBox_Password->SetText(FText::GetEmpty());
	TextBlock_StatusMessage->SetText(FText::GetEmpty());
}
