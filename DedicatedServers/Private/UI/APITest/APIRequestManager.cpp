// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/APITest/APIRequestManager.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Data/API/APIData.h"
#include "GameplayTags/DedicatedServersTags.h"
#include "UI/HTTP/HttpRequestTypes.h"


void UAPIRequestManager::ListFleets()
{
	check(APIData);
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UAPIRequestManager::ListFleets_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameSessionsAPI::ListFleets);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->ProcessRequest();
}

void UAPIRequestManager::ListFleets_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "ListFleets Response Received");

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			OnListFleetsResponseReceived.Broadcast(FDSListFleetsResponse(), false);
			return;
		}
		DumpMetaData(JsonObject);

		FDSListFleetsResponse ListFleetsResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &ListFleetsResponse);
		ListFleetsResponse.Dump();
		
		OnListFleetsResponseReceived.Broadcast(ListFleetsResponse, true);
	}
}
