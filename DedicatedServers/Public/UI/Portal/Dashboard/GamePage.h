// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePage.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UGamePage : public UUserWidget
{
	GENERATED_BODY()

	
protected:
	virtual void NativeConstruct() override;

	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UJoinGameWidget> JoinGameWidget;
	
	UFUNCTION()
	void JoinGameButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameSessionsManager> GameSessionsManagerClass;

	UPROPERTY()
	TObjectPtr<UGameSessionsManager> GameSessionsManager;
};
