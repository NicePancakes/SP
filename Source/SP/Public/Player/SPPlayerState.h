#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPPlayerState.generated.h"


UCLASS()
class SP_API ASPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetTeamID() const { return TeamID; }
	const FLinearColor& GetTeamColor() const { return TeamColor; }

	void SetTeamID(int32 InTeamID) { TeamID = InTeamID; }
	void SetTeamColor(const FLinearColor& InTeamColor) { TeamColor = InTeamColor; }

	void AddKill() { ++KillsNum; };
	void AddDeath() { ++DeathsNum; };

	int32 GetKillsNum() const { return KillsNum; }
	int32 GetDeathsNum() const { return DeathsNum; }

	void LogInfo();

protected:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
