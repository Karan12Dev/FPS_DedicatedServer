// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DS_GameModeBase.h"
#include "Types/DSTypes.h"
#include "DS_MatchGameMode.generated.h"

class UGameStatsManager;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API ADS_MatchGameMode : public ADS_GameModeBase
{
	GENERATED_BODY()

public:
	ADS_MatchGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;


protected:
	virtual void BeginPlay() override;
	virtual void OnCountdownTimerFinished(ECountdownTimerType Type) override;
	void UpdateLeaderboard(const TArray<FString>& LeaderboardNames);
	virtual void OnMatchEnded();

	UFUNCTION()
	void OnLeaderboardUpdated();

	
private:
	UPROPERTY()
	EMatchStatus MatchStatus;

	UPROPERTY(EditDefaultsOnly)
	FCountdownTimerHandle PreMatchTimer;

	UPROPERTY(EditDefaultsOnly)
	FCountdownTimerHandle MatchTimer;

	UPROPERTY(EditDefaultsOnly)
	FCountdownTimerHandle PostMatchTimer;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LobbyMap;

	void SetClientInputEnabled(bool bEnabled);
	void EndMatchForPlayerStates();
	

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameStatsManager> GameStatsManagerClass;
	
	UPROPERTY()
	TObjectPtr<UGameStatsManager> GameStatsManager;
};
