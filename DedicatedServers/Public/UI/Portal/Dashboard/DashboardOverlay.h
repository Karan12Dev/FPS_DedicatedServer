// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DashboardOverlay.generated.h"

class UGameStatsManager;
class UWidgetSwitcher;
class UButton;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UDashboardOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UGamePage> GamePage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCareerPage> CareerPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class ULeaderboardPage>LeaderboardPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Game;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Career;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Leaderboard;

	UFUNCTION()
	void ShowGamePage();
	
	UFUNCTION()
	void ShowCareerPage();
	
	UFUNCTION()
	void ShowLeaderboardPage();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameStatsManager> GameStatsManagerClass;
	
	UPROPERTY()
	TObjectPtr<UGameStatsManager> GameStatsManager;

	void DisableButton(UButton* const Button) const;
};
