
#include "UI/HTTP/HttpRequestTypes.h"
#include "DedicatedServers/DedicatedServers.h"

namespace HTTPStatusMessages
{
	const FString SomethingWentWrong{TEXT("Something Went Wrong!")};
	const FString FoundGameSession{TEXT("Found Game Session")};
}

void FDSMetaData::Dump() const
{
	UE_LOG(LogDedicatedServers, Log, TEXT("Meta Data:"));
	UE_LOG(LogDedicatedServers, Log, TEXT("httpStatusCode: %d"), httpStatusCode);
	UE_LOG(LogDedicatedServers, Log, TEXT("requestId: %s"), *requestId);
	UE_LOG(LogDedicatedServers, Log, TEXT("attempts: %d"), attempts);
	UE_LOG(LogDedicatedServers, Log, TEXT("totalRetryDelay: %f"), totalRetryDelay);
}

void FDSListFleetsResponse::Dump() const
{
	for (const FString& FleetId : FleetIds)
	{
		UE_LOG(LogDedicatedServers, Log, TEXT("Fleet Id: %s"), *FleetId);
	}
	if (!NextToken.IsEmpty())
	{
		UE_LOG(LogDedicatedServers, Log, TEXT("Next Token: %s"), *NextToken);
	}
}

void FDSGameSession::Dump() const
{
	UE_LOG(LogDedicatedServers, Log, TEXT("GameSession:"));
	UE_LOG(LogDedicatedServers, Log, TEXT("Creation Time: %s"), *CreationTime);
	UE_LOG(LogDedicatedServers, Log, TEXT("Creator Id: %s"), *CreatorId);
	UE_LOG(LogDedicatedServers, Log, TEXT("Current Player Session Count: %d"), CurrentPlayerSessionCount);
	UE_LOG(LogDedicatedServers, Log, TEXT("DNS Name: %s"), *DnsName);
	UE_LOG(LogDedicatedServers, Log, TEXT("Fleet ARN: %s"), *FleetArn);
	UE_LOG(LogDedicatedServers, Log, TEXT("Fleet ID: %s"), *FleetId);
	
	UE_LOG(LogDedicatedServers, Log, TEXT("Game Properties:"));
	for (const TPair<FString, FString>& Pair : GameProperties)
	{
		UE_LOG(LogDedicatedServers, Log, TEXT("  %s: %s"), *Pair.Key, *Pair.Value);
	}

	UE_LOG(LogDedicatedServers, Log, TEXT("Game Session Data: %s"), *GameSessionData);
	UE_LOG(LogDedicatedServers, Log, TEXT("Game Session ID: %s"), *GameSessionId);
	UE_LOG(LogDedicatedServers, Log, TEXT("IP Address: %s"), *IpAddress);
	UE_LOG(LogDedicatedServers, Log, TEXT("Location: %s"), *Location);
	UE_LOG(LogDedicatedServers, Log, TEXT("Matchmaker Data: %s"), *MatchmakerData);
	UE_LOG(LogDedicatedServers, Log, TEXT("Maximum Player Session Count: %d"), MaximumPlayerSessionCount);
	UE_LOG(LogDedicatedServers, Log, TEXT("Name: %s"), *Name);
	UE_LOG(LogDedicatedServers, Log, TEXT("Player Session Creation Policy: %s"), *PlayerSessionCreationPolicy);
	UE_LOG(LogDedicatedServers, Log, TEXT("Port: %d"), Port);
	UE_LOG(LogDedicatedServers, Log, TEXT("Status: %s"), *Status);
	UE_LOG(LogDedicatedServers, Log, TEXT("Status Reason: %s"), *StatusReason);
	UE_LOG(LogDedicatedServers, Log, TEXT("Termination Time: %s"), *TerminationTime);
}

void FDSPlayerSession::Dump() const
{
	UE_LOG(LogDedicatedServers, Log, TEXT("PlayerSession:"));
	UE_LOG(LogDedicatedServers, Log, TEXT("  CreationTime: %s"), *CreationTime);
	UE_LOG(LogDedicatedServers, Log, TEXT("  DnsName: %s"), *DnsName);
	UE_LOG(LogDedicatedServers, Log, TEXT("  FleetArn: %s"), *FleetArn);
	UE_LOG(LogDedicatedServers, Log, TEXT("  FleetId: %s"), *FleetId);
	UE_LOG(LogDedicatedServers, Log, TEXT("  GameSessionId: %s"), *GameSessionId);
	UE_LOG(LogDedicatedServers, Log, TEXT("  IpAddress: %s"), *IpAddress);
	UE_LOG(LogDedicatedServers, Log, TEXT("  PlayerData: %s"), *PlayerData);
	UE_LOG(LogDedicatedServers, Log, TEXT("  PlayerId: %s"), *PlayerId);
	UE_LOG(LogDedicatedServers, Log, TEXT("  PlayerSessionId: %s"), *PlayerSessionId);
	UE_LOG(LogDedicatedServers, Log, TEXT("  Port: %d"), Port);
	UE_LOG(LogDedicatedServers, Log, TEXT("  Status: %s"), *Status);
	UE_LOG(LogDedicatedServers, Log, TEXT("  TerminationTime: %s"), *TerminationTime);
}

void FCodeDeliveryDetails::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("  CodeDeliveryDetails:"));
	UE_LOG(LogTemp, Log, TEXT("    AttributeName: %s"), *AttributeName);
	UE_LOG(LogTemp, Log, TEXT("    DeliveryMedium: %s"), *DeliveryMedium);
	UE_LOG(LogTemp, Log, TEXT("    Destination: %s"), *Destination);
}

void FDSSignUpResponse::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("UserSessionResponse Dump:"));
	CodeDeliveryDetails.Dump();
	UE_LOG(LogTemp, Log, TEXT("  Session: %s"), *Session);
	UE_LOG(LogTemp, Log, TEXT("  UserConfirmed: %s"), UserConfirmed ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Log, TEXT("  UserSub: %s"), *UserSub);
}

void FNewDeviceMetadata::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("    NewDeviceMetadata:"));
	UE_LOG(LogTemp, Log, TEXT("      DeviceGroupKey: %s"), *DeviceGroupKey);
	UE_LOG(LogTemp, Log, TEXT("      DeviceKey: %s"), *DeviceKey);
}

void FAuthenticationResult::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("  AuthenticationResult:"));
	UE_LOG(LogTemp, Log, TEXT("    AccessToken: %s"), *AccessToken);
	UE_LOG(LogTemp, Log, TEXT("    ExpiresIn: %d"), ExpiresIn);
	UE_LOG(LogTemp, Log, TEXT("    IdToken: %s"), *IdToken);
	NewDeviceMetadata.Dump();
	UE_LOG(LogTemp, Log, TEXT("    RefreshToken: %s"), *RefreshToken);
	UE_LOG(LogTemp, Log, TEXT("    TokenType: %s"), *TokenType);
}

void FDSInitiateAuthResponse::Dump() const
{
	UE_LOG(LogTemp, Log, TEXT("AuthChallengeResponse Dump:"));
	AuthenticationResult.Dump();
	UE_LOG(LogTemp, Log, TEXT("  AvailableChallenges:"));
	for (const FString& Challenge : AvailableChallenges)
	{
		UE_LOG(LogTemp, Log, TEXT("    - %s"), *Challenge);
	}
	UE_LOG(LogTemp, Log, TEXT("  ChallengeName: %s"), *ChallengeName);
	UE_LOG(LogTemp, Log, TEXT("  ChallengeParameters:"));
	for (const auto& Param : ChallengeParameters)
	{
		UE_LOG(LogTemp, Log, TEXT("    %s: %s"), *Param.Key, *Param.Value);
	}
	UE_LOG(LogTemp, Log, TEXT("  Session: %s"), *Session);
	UE_LOG(LogTemp, Log, TEXT("  Email: %s"), *email);
}

void FDSRetrieveMatchStatsResponse::Dump() const
{
	UE_LOG(LogDedicatedServers, Log, TEXT("FDSRetrieveMatchStatsResponse:"));
	UE_LOG(LogDedicatedServers, Log, TEXT("  highestStreak: %d"), highestStreak);
	UE_LOG(LogDedicatedServers, Log, TEXT("  dethroneElims: %d"), dethroneElims);
	UE_LOG(LogDedicatedServers, Log, TEXT("  gotFirstBlood: %d"), gotFirstBlood);
	UE_LOG(LogDedicatedServers, Log, TEXT("  defeats: %d"), defeats);
	UE_LOG(LogDedicatedServers, Log, TEXT("  scoredElims: %d"), scoredElims);
	UE_LOG(LogDedicatedServers, Log, TEXT("  email: %s"), *email);
	UE_LOG(LogDedicatedServers, Log, TEXT("  misses: %d"), misses);
	UE_LOG(LogDedicatedServers, Log, TEXT("  revengeElims: %d"), revengeElims);
	UE_LOG(LogDedicatedServers, Log, TEXT("  matchLosses: %d"), matchLosses);
	UE_LOG(LogDedicatedServers, Log, TEXT("  showstopperElims: %d"), showstopperElims);
	UE_LOG(LogDedicatedServers, Log, TEXT("  databaseid: %s"), *databaseid);
	UE_LOG(LogDedicatedServers, Log, TEXT("  headShotElims: %d"), headShotElims);
	UE_LOG(LogDedicatedServers, Log, TEXT("  username: %s"), *username);
	UE_LOG(LogDedicatedServers, Log, TEXT("  hits: %d"), hits);
	UE_LOG(LogDedicatedServers, Log, TEXT("  matchWins: %d"), matchWins);
}
