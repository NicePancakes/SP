#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SPGameModeBase.generated.h"

class AAIController;

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "50"))
	int32 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 10; //seconds

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "5", ClampMax = "20"))
	int32 RespawnTime = 15; //seconds

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "5", ClampMax = "20"))
	int32 MinRoundTimeForRespawn = 10; //seconds

	UPROPERTY(EditDefaultsOnly)
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly)
	TArray<FLinearColor> TeamColors;
};

UENUM(BlueprintType)
enum ESPMatchState
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

UCLASS()
class SP_API ASPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMathStateChangedSignature, ESPMatchState)

public:
	ASPGameModeBase();

	virtual void StartPlay() override;

	void Killed(AController* KillerController, AController* VictimController);

	const FGameData& GetGameData() const { return GameData; }
	int32 GetCurrentRoundNum() const { return CurrentRound; }
	int32 GetRoundSecondsRemaining() const { return RoundCountDown; }

	void RespawnRequest(AController* Controller);

	FOnMathStateChangedSignature& GetOnMatchStateChangedSignature() { return OnMathStateChanged; }

	virtual bool ClearPause() override;

protected:
	void SpawnBots();
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;

	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	const FLinearColor& DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();
	void SetMatchState(ESPMatchState State);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	ESPMatchState CurrentMathState = ESPMatchState::WaitingToStart;

	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;

	FOnMathStateChangedSignature OnMathStateChanged;
};
