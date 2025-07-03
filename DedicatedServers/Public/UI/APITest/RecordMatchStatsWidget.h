// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecordMatchStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API URecordMatchStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_RecordMatchStats;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameStatsManager> GameStatsManagerClass;


private:
	UPROPERTY()
	TObjectPtr<UGameStatsManager> GameStatsManager;

	UFUNCTION()
	void RecordMatchStatsButtonClicked();
};
