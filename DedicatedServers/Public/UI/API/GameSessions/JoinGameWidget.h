// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinGameWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UJoinGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_JoinGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StatusMessage;

	UFUNCTION()
	void SetStatusMessage(const FString& StatusMessage, bool bShouldResetMessage);
};
