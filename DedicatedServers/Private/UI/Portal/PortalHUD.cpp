// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/PortalHUD.h"
#include "UI/Portal/SignIn/SignInOverlay.h"
#include "UI/Portal/Dashboard/DashboardOverlay.h"


void APortalHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(SignInOverlayClass)) return;
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	SignInOverlay = CreateWidget<USignInOverlay>(OwningPlayerController, SignInOverlayClass);
	if (IsValid(SignInOverlay))
	{
		SignInOverlay->AddToViewport();
	}
	FInputModeGameAndUI InputModeData;
	OwningPlayerController->SetInputMode(InputModeData);
	OwningPlayerController->SetShowMouseCursor(true);
}

void APortalHUD::OnSignIn()
{
	if (!IsValid(DashboardOverlayClass)) return;
	
	if (IsValid(SignInOverlay))
	{
		SignInOverlay->RemoveFromParent();
	}
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	DashboardOverlay = CreateWidget<UDashboardOverlay>(OwningPlayerController, DashboardOverlayClass);
	if (IsValid(DashboardOverlay))
	{
		DashboardOverlay->AddToViewport();
	}
}

void APortalHUD::OnSignOut()
{
	if (!IsValid(SignInOverlayClass)) return;
	
	if (IsValid(DashboardOverlay))
	{
		DashboardOverlay->RemoveFromParent();
	}
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	SignInOverlay = CreateWidget<USignInOverlay>(OwningPlayerController, SignInOverlayClass);
	if (IsValid(SignInOverlay))
	{
		SignInOverlay->AddToViewport();
	}
}
