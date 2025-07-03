// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/DSTypes.h"
#include "TimerWidget.generated.h"

class ADSPlayerController;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECountdownTimerType TimerType = ECountdownTimerType::None;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ADSPlayerController> OwningPlayerController;

	UFUNCTION()
	virtual void OnTimerUpdated(float CountdownTimeLeft, ECountdownTimerType Type);

	UFUNCTION()
	virtual void OnTimerStopped(float CountdownTimeLeft, ECountdownTimerType Type);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Started"))
	void K2_OnTimerStarted(float Time, ECountdownTimerType Type);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Updated"))
	void K2_OnTimerUpdated(float Time, ECountdownTimerType Type);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Timer Stopped"))
	void K2_OnTimerStopped(float Time, ECountdownTimerType Type);

	
private:
	FString FormatTimeAsString(float TimeSeconds) const;
	void TimerStarted(float InitialTime);
	void TimerStopped();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Time;

	float InternalCountdown;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bActive = false;

	UPROPERTY(EditDefaultsOnly)
	bool bCanBeNegative = false;
	
	UPROPERTY(EditDefaultsOnly)
	bool bShowCentiSeconds = false;

	UPROPERTY(EditDefaultsOnly)
	bool bHiddenWhenInActive = true;

	void UpdateCountdown(float TimeSeconds);
};
