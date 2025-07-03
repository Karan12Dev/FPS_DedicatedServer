// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/APITest/APITestOverlay.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "UI/API/ListFleets/ListFleetsBox.h"
#include "UI/APITest/APIRequestManager.h"
#include "UI/HTTP/HttpRequestTypes.h"
#include "UI/API/ListFleets/FleetID.h"


void UAPITestOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	check(APIRequestManagerClass);
	APIRequestManager = NewObject<UAPIRequestManager>(this, APIRequestManagerClass);
	check(ListFleetsBox);
	check(ListFleetsBox->Button_ListFleets);
	ListFleetsBox->Button_ListFleets->OnClicked.AddDynamic(this, &UAPITestOverlay::ListFleetsButtonClicked);
}

void UAPITestOverlay::ListFleetsButtonClicked()
{
	check(APIRequestManagerClass);
	APIRequestManager->OnListFleetsResponseReceived.AddDynamic(this, &UAPITestOverlay::OnListFleetsResponseReceived);
	APIRequestManager->ListFleets();
	ListFleetsBox->Button_ListFleets->SetIsEnabled(false);
}

void UAPITestOverlay::OnListFleetsResponseReceived(const FDSListFleetsResponse& ListFleetsResponse, bool bWasSuccessful)
{
	if (APIRequestManager->OnListFleetsResponseReceived.IsAlreadyBound(this, &UAPITestOverlay::OnListFleetsResponseReceived))
	{
		APIRequestManager->OnListFleetsResponseReceived.RemoveDynamic(this, &UAPITestOverlay::OnListFleetsResponseReceived);
	}
	ListFleetsBox->ScrollBox_ListFleets->ClearChildren();
	if (bWasSuccessful)
	{
		for (const FString& FleetId : ListFleetsResponse.FleetIds)
		{
			UFleetID* FleetIdWidget = CreateWidget<UFleetID>(this, FleetIDWidgetClass);
			FleetIdWidget->TextBlock_FleetID->SetText(FText::FromString(FleetId));
			ListFleetsBox->ScrollBox_ListFleets->AddChild(FleetIdWidget);
		}
	}
	else
	{
		UFleetID* FleetIdWidget = CreateWidget<UFleetID>(this, FleetIDWidgetClass);
		FleetIdWidget->TextBlock_FleetID->SetText(FText::FromString(TEXT("Something went wrong!")));
		ListFleetsBox->ScrollBox_ListFleets->AddChild(FleetIdWidget);
	}
	ListFleetsBox->Button_ListFleets->SetIsEnabled(true);
}
