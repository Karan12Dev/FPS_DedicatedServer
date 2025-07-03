// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/AccountDropdown_Expanded.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/Portal/PortalManager.h"
#include "Player/DSLocalPlayerSubsystem.h"


void UAccountDropdown_Expanded::NativeConstruct()
{
	Super::NativeConstruct();
	
	PortalManager = NewObject<UPortalManager>(this, PortalManagerClass);

	Button_SignOut->OnHovered.AddDynamic(this, &UAccountDropdown_Expanded::SignOutButton_Hover);
	Button_SignOut->OnUnhovered.AddDynamic(this, &UAccountDropdown_Expanded::SignOutButton_Unhover);
	Button_SignOut->OnClicked.AddDynamic(this, &UAccountDropdown_Expanded::SignOutButton_OnClicked);

	UDSLocalPlayerSubsystem* LocalPlayerSubsystem = GetDSLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		TextBlock_Email->SetText(FText::FromString(LocalPlayerSubsystem->Email));
	}
}

void UAccountDropdown_Expanded::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetSignOutButtonStyleTransparent();
	SignOutButton_Unhover();
}

void UAccountDropdown_Expanded::SetSignOutButtonStyleTransparent()
{
	FButtonStyle Style;
	FSlateBrush Brush;
	Brush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
	Style.Disabled = Brush;
	Style.Hovered = Brush;
	Style.Pressed = Brush;
	Style.Normal = Brush;
	Button_SignOut->SetStyle(Style);
}

void UAccountDropdown_Expanded::SignOutButton_Hover()
{
	TextBlock_SignOut->SetColorAndOpacity(HoveredTextColor);
}

void UAccountDropdown_Expanded::SignOutButton_Unhover()
{
	TextBlock_SignOut->SetColorAndOpacity(UnhoveredTextColor);
}

void UAccountDropdown_Expanded::SignOutButton_OnClicked()
{
	if (!IsValid(PortalManager)) return;
	
	Button_SignOut->SetIsEnabled(false);

	UDSLocalPlayerSubsystem* LocalPlayerSubsystem = GetDSLocalPlayerSubsystem();
	if (IsValid(LocalPlayerSubsystem))
	{
		FAuthenticationResult AuthResult = LocalPlayerSubsystem->GetAuthResult();
		PortalManager->SignOut(AuthResult.AccessToken);
	}
}

UDSLocalPlayerSubsystem* UAccountDropdown_Expanded::GetDSLocalPlayerSubsystem()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController) && IsValid(PlayerController->GetLocalPlayer()))
	{
		UDSLocalPlayerSubsystem* LocalPlayerSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UDSLocalPlayerSubsystem>();
		if (IsValid(LocalPlayerSubsystem))
		{
			return LocalPlayerSubsystem;
		}
	}
	return nullptr;
}
