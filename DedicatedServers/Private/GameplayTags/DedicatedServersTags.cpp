
#include "GameplayTags/DedicatedServersTags.h"

namespace DedicatedServersTags
{
	namespace GameSessionsAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ListFleets, "DedicatedServersTags.GameSessionsAPI.ListFleets", "List Fleets resource on the GameSession API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(FindOrCreateGameSession, "DedicatedServersTags.GameSessionsAPI.FindOrCreateGameSession", "Retrives an ACTIVE game session, creating one if one doesn't exist on the gamesessions API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CreatePlayerSession, "DedicatedServersTags.GameSessionsAPI.CreatePlayerSession", "Creating the Player Session on the GameSession API")
	}
	
	namespace PortalAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignUp, "DedicatedServersTags.PortalAPI.SignUp", "Creates a new User in the Portal API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ConfirmSignUp, "DedicatedServersTags.PortalAPI.ConfirmSignUp", "Confirms a new user in Portal API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignIn, "DedicatedServersTags.PortalAPI.SignIn", "Retrieves Access Token, Id Token, and Refresh Token in Portal API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignOut, "DedicatedServersTags.PortalAPI.SignOut", "Signs user out and invalidates tokens in Portal API")
	}
	
	namespace GameStatsAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(RecordMatchStats, "DedicatedServersTags.GameStatsAPI.RecordMatchStats", "Record the stats of the match in Game Stats API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(RetrieveMatchStats, "DedicatedServersTags.GameStatsAPI.RetrieveMatchStats", "Gets the match stats form the Players table in Game Stats API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(UpdateLeaderboard, "DedicatedServersTags.GameStatsAPI.UpdateLeaderboard", "Updates the leaderboard in Game Stats API")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(RetrieveLeaderboard, "DedicatedServersTags.GameStatsAPI.RetrieveLeaderboard", "Retrieves the leaderboard in Game Stats API")
	}
}