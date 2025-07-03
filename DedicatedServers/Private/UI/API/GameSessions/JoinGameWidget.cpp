// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/API/GameSessions/JoinGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UJoinGameWidget::SetStatusMessage(const FString& StatusMessage, bool bShouldResetMessag)
{
	TextBlock_StatusMessage->SetText(FText::FromString(StatusMessage));
	if (bShouldResetMessag)
	{
		Button_JoinGame->SetIsEnabled(true);
	}
}
