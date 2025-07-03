// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Interfaces/HUDManagement.h"
#include "PortalHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API APortalHUD : public AHUD, public IHUDManagement
{
	GENERATED_BODY()

public:
	// IHUDManagement
	virtual void OnSignIn() override;
	virtual void OnSignOut() override;
	
	
protected:
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USignInOverlay> SignInOverlayClass;
	
	UPROPERTY()
	TObjectPtr<USignInOverlay> SignInOverlay;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDashboardOverlay> DashboardOverlayClass;

	UPROPERTY()
	TObjectPtr<UDashboardOverlay> DashboardOverlay;
};
