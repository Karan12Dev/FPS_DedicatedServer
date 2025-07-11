// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "APITestHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API AAPITestHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UAPITestOverlay> APITestOverlayClass;

	UPROPERTY()
	TObjectPtr<UAPITestOverlay> APITestOverlay;


protected:
	virtual void BeginPlay() override;
};
