// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/PortalManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/API/APIData.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Player/DSLocalPlayerSubsystem.h"
#include "UI/Interfaces/HUDManagement.h"


void UPortalManager::SignIn(const FString& UserName, const FString& Password)
{
	if (!IsValid(APIData)) return;
	SignInStatusMessageDelegate.Broadcast(TEXT("Signing in..."), false);
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPortalManager::SignIn_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignIn);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	LastUserName = UserName;
	TMap<FString, FString> Params {
			{ TEXT("username"), UserName },
			{ TEXT("password"), Password }
	};
	Request->SetContentAsString(SerializeJsonContent(Params));
	Request->ProcessRequest();
}

void UPortalManager::SignIn_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		SignInStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
	}
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			SignInStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
			return;
		}

		FDSInitiateAuthResponse InitiateAuthResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &InitiateAuthResponse);
		InitiateAuthResponse.Dump();
		//OnSignInSucceeded.Broadcast();

		UDSLocalPlayerSubsystem* LocalPlayerSubsystem = GetDSLocalPlayerSubsystem();
		if (IsValid(LocalPlayerSubsystem))
		{
			LocalPlayerSubsystem->InitializeTokens(InitiateAuthResponse.AuthenticationResult, this);
			LocalPlayerSubsystem->Username = LastUserName;
			LocalPlayerSubsystem->Email = InitiateAuthResponse.email;
		}

		APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
		if (IsValid(LocalPlayerController))
		{
			if (IHUDManagement* HUDManagement = Cast<IHUDManagement>(LocalPlayerController->GetHUD()))
			{
				HUDManagement->OnSignIn();
			}
		}
	}
}

void UPortalManager::SignOut(const FString& AccessToken)
{
	if (!IsValid(APIData)) return;
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPortalManager::SignOut_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignOut);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	TMap<FString, FString> Params {
				{ TEXT("accessToken"), AccessToken }
	};
	Request->SetContentAsString(SerializeJsonContent(Params));
	Request->ProcessRequest();
}

void UPortalManager::SignOut_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		return;
	}
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			return;
		}
	}
	if (UDSLocalPlayerSubsystem* LocalPlayerSubsystem = GetDSLocalPlayerSubsystem();IsValid(LocalPlayerSubsystem))
	{
		LocalPlayerSubsystem->Username = "";
		LocalPlayerSubsystem->Password = "";
		LocalPlayerSubsystem->Email = "";
	}
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		if (IHUDManagement* HUDManagement = Cast<IHUDManagement>(LocalPlayerController->GetHUD()))
		{
			HUDManagement->OnSignOut();
		}
	}
}

void UPortalManager::SignUp(const FString& UserName, const FString& Password, const FString& Email)
{
	if (!IsValid(APIData)) return;
	SignUpStatusMessageDelegate.Broadcast(TEXT("Creating a new account..."), false);
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPortalManager::SignUp_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignUp);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	LastUserName = UserName;
	TMap<FString, FString> Params {
		{ TEXT("username"), UserName },
		{ TEXT("password"), Password },
		{ TEXT("email"), Email}
	};
	Request->SetContentAsString(SerializeJsonContent(Params));
	Request->ProcessRequest();
}

void UPortalManager::SignUp_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		SignUpStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
	}
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			SignUpStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
			return;
		}
		
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &LastSignupResponse);
		OnSignUpSucceeded.Broadcast();
	}
}

void UPortalManager::Confirm(const FString& ConfirmationCode)
{
	if (!IsValid(APIData)) return;
	ConfirmStatusMessageDelegate.Broadcast(TEXT("Checking verification code..."), false);
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPortalManager::Confirm_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::ConfirmSignUp);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("PUT"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	TMap<FString, FString> Params {
			{ TEXT("username"), LastUserName },
			{ TEXT("confirmationCode"), ConfirmationCode }
	};
	Request->SetContentAsString(SerializeJsonContent(Params));
	Request->ProcessRequest();
}

void UPortalManager::Confirm_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		ConfirmStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
	}
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject))
		{
			if (JsonObject->HasField((TEXT("name"))))
			{
				const FString Exception = JsonObject->GetStringField(TEXT("name"));
				if (Exception.Equals(TEXT("CodeMismatchException")))
				{
					ConfirmStatusMessageDelegate.Broadcast(TEXT("Wrong Code"), true);
					return;
				}
			}
			ConfirmStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
			return;
		}
	}
	OnConfirmSucceeded.Broadcast();
}

void UPortalManager::QuitGame()
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (IsValid(LocalPlayerController))
	{
		UKismetSystemLibrary::QuitGame(this, LocalPlayerController, EQuitPreference::Quit, false);
	}
}

void UPortalManager::RefreshTokens(const FString& RefreshToken)
{
	if (!IsValid(APIData)) return;
	TSharedRef<IHttpRequest> Request =  FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UPortalManager::RefreshTokens_Response);
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignIn);
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	TMap<FString, FString> Params {
				{ TEXT("refreshToken"), RefreshToken }
	};
	Request->SetContentAsString(SerializeJsonContent(Params));
	Request->ProcessRequest();
}

void UPortalManager::RefreshTokens_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful) return;
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (ContainsErrors(JsonObject)) return;

		FDSInitiateAuthResponse InitiateAuthResponse;
		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &InitiateAuthResponse);

		UDSLocalPlayerSubsystem* LocalPlayerSubsystem = GetDSLocalPlayerSubsystem();
		if (IsValid(LocalPlayerSubsystem))
		{
			LocalPlayerSubsystem->UpdateTokens(InitiateAuthResponse.AuthenticationResult.AccessToken, InitiateAuthResponse.AuthenticationResult.IdToken);
		}
	}
}
