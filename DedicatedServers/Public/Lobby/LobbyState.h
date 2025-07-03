// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerInfo.h"
#include "GameFramework/Info.h"
#include "LobbyState.generated.h"

USTRUCT()
struct FLobbyPlayerInfoDelta
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FLobbyPlayerInfo> AddedPlayers{};
	
	UPROPERTY()
	TArray<FLobbyPlayerInfo> RemovedPlayers{};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoChanged, const FLobbyPlayerInfo&, PlayerInfo);

UCLASS()
class DEDICATEDSERVERS_API ALobbyState : public AInfo
{
	GENERATED_BODY()

public:
	ALobbyState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void AddPlayerInfo(const FLobbyPlayerInfo& PlayerInfo);
	void RemovePlayerInfo(const FString& Username);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerInfoChanged OnPlayerInfoAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerInfoChanged OnPlayerInfoRemovedDelegate;

	
protected:
	UFUNCTION()
	void OnRep_LobbyPlayerInfo();


private:
	UPROPERTY(ReplicatedUsing = OnRep_LobbyPlayerInfo)
	FLobbyPlayerInfoArray PlayerInfoArray;
	
	UPROPERTY()
	FLobbyPlayerInfoArray LastPlayerInfoArray;

	FLobbyPlayerInfoDelta ComputeInfoPlayerDelta(const TArray<FLobbyPlayerInfo>& OldArray, const TArray<FLobbyPlayerInfo>& NewArray);


public:
	TArray<FLobbyPlayerInfo> GetPlayers() const;
};
