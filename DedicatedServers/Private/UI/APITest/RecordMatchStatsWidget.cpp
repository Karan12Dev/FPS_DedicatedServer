// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/APITest/RecordMatchStatsWidget.h"
#include "UI/GameStats/GameStatsManager.h"
#include "UI/HTTP/HttpRequestTypes.h"
#include "Player/DSLocalPlayerSubsystem.h"
#include "Components/Button.h"

void URecordMatchStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameStatsManager = NewObject<UGameStatsManager>(this, GameStatsManagerClass);
	Button_RecordMatchStats->OnClicked.AddDynamic(this, &URecordMatchStatsWidget::RecordMatchStatsButtonClicked);
}

void URecordMatchStatsWidget::RecordMatchStatsButtonClicked()
{
	check(GameStatsManager);

	const FString Username = TEXT("Karan");
	FDSRecordMatchStatsInput RecordMatchStatsInput;
	RecordMatchStatsInput.username = Username;
	RecordMatchStatsInput.matchStats.hits = 3;
	RecordMatchStatsInput.matchStats.headShotElims = 8;

	GameStatsManager->RecordMatchStats(RecordMatchStatsInput);
}
