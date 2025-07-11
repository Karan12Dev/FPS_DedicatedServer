// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Portal/Dashboard/CareerPage.h"
#include "ShooterCareerPage.generated.h"

struct FDSRetrieveMatchStatsResponse;
class USpecialElimData;
class UCareerAchievement;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UShooterCareerPage : public UCareerPage
{
	GENERATED_BODY()

public:
	virtual void OnRetrieveMatchStats(const FDSRetrieveMatchStatsResponse& RetrieveMatchStatsResponse) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpecialElimData> SpecialElimData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCareerAchievement> CareerAchievementClass;
};
