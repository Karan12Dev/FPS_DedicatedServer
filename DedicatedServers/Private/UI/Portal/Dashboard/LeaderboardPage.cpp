// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/Dashboard/LeaderboardPage.h"
#include "Components/ScrollBox.h"
#include "UI/HTTP/HttpRequestTypes.h"
#include "UI/Portal/Dashboard/LeaderboardCard.h"
#include "Components/TextBlock.h"


void ULeaderboardPage::PopulateLeaderboard(TArray<FDSLeaderboardItem>& Leaderboard)
{
	ScrollBox_Leaderboard->ClearChildren();
	CalculateLeaderboardPlaces(Leaderboard);
	
	for (const FDSLeaderboardItem& Item : Leaderboard)
	{
		ULeaderboardCard* LeaderboardCard = CreateWidget<ULeaderboardCard>(this, LeaderboardCardClass);
		if (IsValid(LeaderboardCard))
		{
			LeaderboardCard->SetPlayerInfo(Item.username, Item.matchWins, Item.place);
			ScrollBox_Leaderboard->AddChild(LeaderboardCard);
		}
	}
}

void ULeaderboardPage::CalculateLeaderboardPlaces(TArray<FDSLeaderboardItem>& OutLeaderboard)
{
	OutLeaderboard.Sort([](const FDSLeaderboardItem& A, const FDSLeaderboardItem& B)
	{
		return A.matchWins > B.matchWins;
	});
	int32 CurrentRank = 1;
	for (int32 i = 0; i < OutLeaderboard.Num(); ++i)
	{
		if (i > 0 && OutLeaderboard[i].matchWins == OutLeaderboard[i - 1].matchWins)
		{
			OutLeaderboard[i].place = OutLeaderboard[i - 1].place;
		}
		else
		{
			OutLeaderboard[i].place = CurrentRank;
		}
		CurrentRank++;
	}
}

void ULeaderboardPage::SetStatusMessage(const FString& StatusMessage, bool bShouldResetWidgets)
{
	TextBlock_StatusMessage->SetText(FText::FromString(StatusMessage));
}
