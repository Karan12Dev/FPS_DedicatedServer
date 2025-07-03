// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "APITestOverlay.generated.h"

struct FDSListFleetsResponse;

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UAPITestOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListFleetsBox> ListFleetsBox;

	UPROPERTY()
	TObjectPtr<class UAPIRequestManager> APIRequestManager;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAPIRequestManager> APIRequestManagerClass;

	UFUNCTION()
	void ListFleetsButtonClicked();

	UFUNCTION()
	void OnListFleetsResponseReceived(const FDSListFleetsResponse& ListFleetsResponse, bool bWasSuccessful);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UFleetID> FleetIDWidgetClass;
};
