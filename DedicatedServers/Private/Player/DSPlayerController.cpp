// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DSPlayerController.h"



ADSPlayerController::ADSPlayerController()
{
	SingleTripTime = 0.f;
	Username = "";
	PlayerSessionId = "";
}

void ADSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetNetMode() == NM_Standalone)
	{
		DisableInput(this);
	}
}

void ADSPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (GetNetMode() == NM_Standalone) return;
	if (IsLocalController())
	{
		Server_Ping(GetWorld()->GetTimeSeconds());
	}
}

void ADSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if  (IsLocalController())
	{
		DisableInput(this);
	}
}

void ADSPlayerController::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	if  (IsLocalController())
	{
		Server_Ping(GetWorld()->GetTimeSeconds());
		DisableInput(this);
	}
}

void ADSPlayerController::Client_SetInputEnabled_Implementation(bool bEnabled)
{
	if (bEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

void ADSPlayerController::Server_Ping_Implementation(float TimeOfRequest)
{
	Client_Pong(TimeOfRequest);
}

void ADSPlayerController::Client_Pong_Implementation(float TimeOfRequest)
{
	const float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfRequest;
	SingleTripTime = RoundTripTime * 0.5f;
}

void ADSPlayerController::Client_TimerUpdated_Implementation(float CountDownTimeLeft, ECountdownTimerType Type) const
{
	OnTimerUpdatedDelegate.Broadcast(CountDownTimeLeft - SingleTripTime, Type);
}

void ADSPlayerController::Client_TimerStopped_Implementation(float CountDownTimeLeft, ECountdownTimerType Type) const
{
	OnTimerStoppedDelegate.Broadcast(CountDownTimeLeft - SingleTripTime, Type);
}
