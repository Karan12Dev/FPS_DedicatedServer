// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignUpPage.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"


void USignUpPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets)
{
	TextBlock_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		Button_SignUp->SetIsEnabled(true);
	}
}

void USignUpPage::ClearTextBoxes()
{
	TextBox_UserName->SetText(FText::GetEmpty());
	TextBox_Password->SetText(FText::GetEmpty());
	TextBox_ConfirmPassword->SetText(FText::GetEmpty());
	TextBox_Email->SetText(FText::GetEmpty());
}

void USignUpPage::NativeConstruct()
{
	Super::NativeConstruct();

	TextBox_UserName->OnTextChanged.AddDynamic(this, &USignUpPage::UpdateSignUpButtonState);
	TextBox_Password->OnTextChanged.AddDynamic(this, &USignUpPage::UpdateSignUpButtonState);
	TextBox_ConfirmPassword->OnTextChanged.AddDynamic(this, &USignUpPage::UpdateSignUpButtonState);
	TextBox_Email->OnTextChanged.AddDynamic(this, &USignUpPage::UpdateSignUpButtonState);
	Button_SignUp->SetIsEnabled(false);
}

void USignUpPage::UpdateSignUpButtonState(const FText& Text)
{
	const bool bIsUsernameValid = !TextBox_UserName->GetText().ToString().IsEmpty();
	const bool bPasswordEqual = TextBox_Password->GetText().ToString() == TextBox_ConfirmPassword->GetText().ToString();
	const bool bEmailValid = IsValidEmail(TextBox_Email->GetText().ToString());
	const bool bIsPasswordLongEnough = TextBox_Password->GetText().ToString().Len() >= 8;

	FString StatusMessage;
	const bool bIsStrongPassword = IsStrongPassword(TextBox_Password->GetText().ToString(), StatusMessage);
	if (!bIsStrongPassword)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(StatusMessage));
	}
	else if (!bIsUsernameValid)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Please enter a valid Username.")));
	}
	else if (!bPasswordEqual)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Please ensure that passwords match.")));
	}
	else if (!bEmailValid)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Please enter a valid Email.")));
	}
	else if (!bIsPasswordLongEnough)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Passwords must be at least 8 characters.")));
	}
	else
	{
		TextBlock_StatusMessage->SetText(FText::GetEmpty());
	}
	Button_SignUp->SetIsEnabled(bIsUsernameValid && bPasswordEqual && bEmailValid && bIsStrongPassword);
}

bool USignUpPage::IsValidEmail(const FString& Email)
{
	const FRegexPattern  EmailPattern(TEXT(R"((^[^\s@]+@[^\s@]+\.[^\s@]{2,}$))"));
	FRegexMatcher Matcher(EmailPattern, Email);
	return Matcher.FindNext();
}

bool USignUpPage::IsStrongPassword(const FString& Password, FString& StatusMessage)
{
	const FRegexPattern NumberPattern(TEXT(R"(\d)"));
	const FRegexPattern SpecialCharPattern(TEXT(R"([^\w\s])"));
	const FRegexPattern UpperCasePattern(TEXT(R"([A-Z])"));
	const FRegexPattern LowerCasePattern(TEXT(R"([a-z])"));

	FRegexMatcher NumberMatcher(NumberPattern, Password);
	FRegexMatcher SpecialCharMatcher(SpecialCharPattern, Password);
	FRegexMatcher UpperCaseMatcher(UpperCasePattern, Password);
	FRegexMatcher LowerCaseMatcher(LowerCasePattern, Password);

	if (!NumberMatcher.FindNext())
	{
		StatusMessage = TEXT("Password must contain at least one number.");
		return false;
	}
	if (!SpecialCharMatcher.FindNext())
	{
		StatusMessage = TEXT("Password must contain at least one special character.");
		return false;
	}
	if (!UpperCaseMatcher.FindNext())
	{
		StatusMessage = TEXT("Password must contain at least one Uppercase character.");
		return false;
	}
	if (!LowerCaseMatcher.FindNext())
	{
		StatusMessage = TEXT("Password must contain at least one lowercase character.");
		return false;
	}
	return true;
}
