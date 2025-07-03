// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/Dashboard/DashboardOverlay.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "UI/GameStats/GameStatsManager.h"
#include "UI/Portal/Dashboard/GamePage.h"
#include "UI/Portal/Dashboard/CareerPage.h"
#include "UI/Portal/Dashboard/LeaderboardPage.h"


void UDashboardOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	GameStatsManager = NewObject<UGameStatsManager>(this, GameStatsManagerClass);
	GameStatsManager->OnRetrieveMatchStatsResponseReceivedDelegate.AddDynamic(CareerPage, &UCareerPage::UCareerPage::OnRetrieveMatchStats);
	GameStatsManager->RetrieveMatchStatsStatusMessageDelegate.AddDynamic(CareerPage, &UCareerPage::SetStatusMessage);
	GameStatsManager->OnRetrieveLeaderboardDelegate.AddDynamic(LeaderboardPage, &ULeaderboardPage::PopulateLeaderboard);
	GameStatsManager->RetrieveLeaderboardStatusMessageDelegate.AddDynamic(LeaderboardPage, &ULeaderboardPage::SetStatusMessage);
	
	Button_Game->OnClicked.AddDynamic(this, &UDashboardOverlay::ShowGamePage);
	Button_Career->OnClicked.AddDynamic(this, &UDashboardOverlay::ShowCareerPage);
	Button_Leaderboard->OnClicked.AddDynamic(this, &UDashboardOverlay::ShowLeaderboardPage);

	ShowGamePage();
}

void UDashboardOverlay::ShowGamePage()
{
	if (IsValid(WidgetSwitcher) && IsValid(GamePage))
	{
		DisableButton(Button_Game);
		WidgetSwitcher->SetActiveWidget(GamePage);
	}
}

void UDashboardOverlay::ShowCareerPage()
{
	if (IsValid(WidgetSwitcher) && IsValid(CareerPage))
	{
		DisableButton(Button_Career);
		WidgetSwitcher->SetActiveWidget(CareerPage);
		if (IsValid(GameStatsManager))
		{
			GameStatsManager->RetrieveMatchStats();
		}
	}
}

void UDashboardOverlay::ShowLeaderboardPage()
{
	if (IsValid(WidgetSwitcher) && IsValid(LeaderboardPage))
	{
		DisableButton(Button_Leaderboard);
		WidgetSwitcher->SetActiveWidget(LeaderboardPage);
		if (IsValid(GameStatsManager))
		{
			GameStatsManager->RetrieveLeaderboard();
		}
	}
}

void UDashboardOverlay::DisableButton(UButton* const Button) const
{
	Button_Game->SetIsEnabled(true);
	Button_Career->SetIsEnabled(true);
	Button_Leaderboard->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}
