// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DS_MatchGameMode.h"
#include "Player/DSPlayerController.h"
#include "Player/DS_MatchPlayerState.h"
#include "UI/GameStats/GameStatsManager.h"


ADS_MatchGameMode::ADS_MatchGameMode()
{
	bUseSeamlessTravel = true;
	MatchStatus = EMatchStatus::WaitingForPlayers;
	PreMatchTimer.Type = ECountdownTimerType::PreMatch;
	MatchTimer.Type = ECountdownTimerType::Match;
	PostMatchTimer.Type = ECountdownTimerType::PostMatch;
}

void ADS_MatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStatsManager = NewObject<UGameStatsManager>(this, GameStatsManagerClass);
	GameStatsManager->OnUpdateLeaderboardSucceededDelegate.AddDynamic(this, &ADS_MatchGameMode::OnLeaderboardUpdated);
}

void ADS_MatchGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (MatchStatus == EMatchStatus::WaitingForPlayers)
	{
		MatchStatus = EMatchStatus::PreMatch;
		StartCountDownTimer(PreMatchTimer);
	}
}

void ADS_MatchGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	RemovePlayerSession(Exiting);
}

void ADS_MatchGameMode::InitSeamlessTravelPlayer(AController* NewController)
{
	Super::InitSeamlessTravelPlayer(NewController);

	if (MatchStatus == EMatchStatus::WaitingForPlayers)
	{
		MatchStatus = EMatchStatus::PreMatch;
		StartCountDownTimer(PreMatchTimer);
	}
}

void ADS_MatchGameMode::OnCountdownTimerFinished(ECountdownTimerType Type)
{
	Super::OnCountdownTimerFinished(Type);

	if (Type == ECountdownTimerType::PreMatch)
	{
		StopCountDownTimer(PreMatchTimer);
		MatchStatus = EMatchStatus::Match;
		StartCountDownTimer(MatchTimer);
		SetClientInputEnabled(true);
	}
	if (Type == ECountdownTimerType::Match)
	{
		StopCountDownTimer(MatchTimer);
		MatchStatus = EMatchStatus::PostMatch;
		StartCountDownTimer(PostMatchTimer);
		SetClientInputEnabled(false);
		OnMatchEnded();
	}
	if (Type == ECountdownTimerType::PostMatch)
	{
		StopCountDownTimer(PostMatchTimer);
		MatchStatus = EMatchStatus::SeamlessTravelling;
		TrySeamlessTravel(LobbyMap);
	}
}

void ADS_MatchGameMode::SetClientInputEnabled(bool bEnabled)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ADSPlayerController* DSPlayerController = Cast<ADSPlayerController>(Iterator->Get());
		if (IsValid(DSPlayerController))
		{
			DSPlayerController->Client_SetInputEnabled(bEnabled);
		}
	}
}

void ADS_MatchGameMode::EndMatchForPlayerStates()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (ADSPlayerController* DSPlayerController = Cast<ADSPlayerController>(Iterator->Get()); IsValid(DSPlayerController))
		{
			if (ADS_MatchPlayerState* MatchPlayerState = DSPlayerController->GetPlayerState<ADS_MatchPlayerState>(); IsValid(MatchPlayerState))
			{
				MatchPlayerState->OnMatchEnded(DSPlayerController->Username);
			}
		}
	}
}

void ADS_MatchGameMode::OnMatchEnded()
{
}

void ADS_MatchGameMode::UpdateLeaderboard(const TArray<FString>& LeaderboardNames)
{
	if (IsValid(GameStatsManager))
	{
		GameStatsManager->UpdateLeaderboard(LeaderboardNames);
	}
}

void ADS_MatchGameMode::OnLeaderboardUpdated()
{
	EndMatchForPlayerStates();
}
