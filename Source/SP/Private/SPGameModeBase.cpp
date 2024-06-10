#include "SPGameModeBase.h"

#include "AIController.h"
#include "Player/SPBaseCharacter.h"
#include "Player/SPPlayerController.h"
#include "UI/SPGameHUD.h"
#include "AIController.h"
#include "Player/SPPlayerState.h"
#include "Components/SPRespawnComponent.h"
#include "EngineUtils.h"
#include "SPGameInstance.h"

ASPGameModeBase::ASPGameModeBase()
{
	DefaultPawnClass = ASPBaseCharacter::StaticClass();
	PlayerControllerClass = ASPPlayerController::StaticClass();
	HUDClass = ASPGameHUD::StaticClass();
	PlayerStateClass = ASPPlayerState::StaticClass();
}

void ASPGameModeBase::StartPlay()
{
	Super::StartPlay();

	USPGameInstance* GameInstance = Cast<USPGameInstance>(GetGameInstance());
	GameData.PlayersNum = GameInstance->GetPlayerNum();
	
	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();
	
	SetMatchState(ESPMatchState::InProgress);
}

void ASPGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	ASPPlayerState* KillerPlayerState = IsValid(KillerController) ? Cast<ASPPlayerState>(KillerController->PlayerState) : nullptr;
	ASPPlayerState* VictimPlayerState = IsValid(VictimController) ? Cast<ASPPlayerState>(VictimController->PlayerState) : nullptr;

	if(IsValid(KillerPlayerState))
	{
		KillerPlayerState->AddKill();
	}

	if(IsValid(VictimPlayerState))
	{
		VictimPlayerState->AddDeath();
		StartRespawn(VictimController);
	}
}

void ASPGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool ASPGameModeBase::ClearPause()
{
	bool IsPauseCleared = Super::ClearPause();
	if(IsPauseCleared)
	{
		SetMatchState(ESPMatchState::InProgress);
	}
	return IsPauseCleared;
}

void ASPGameModeBase::SpawnBots()
{
	for(int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, ActorSpawnParameters);
		RestartPlayer(AIController);
	}
}

UClass* ASPGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(IsValid(InController) && InController->IsA<AAIController>())
	{
		return  AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool ASPGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	bool bIsPauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if(bIsPauseSet)
	{
		SetMatchState(ESPMatchState::Pause);
	}
	return bIsPauseSet;
}

void ASPGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorld()->GetTimerManager().SetTimer(GameRoundTimerHandle, this, &ThisClass::GameTimerUpdate, 1.0f, true);
}

void ASPGameModeBase::GameTimerUpdate()
{	
	if(--RoundCountDown == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(GameRoundTimerHandle);
		if(CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASPGameModeBase::ResetPlayers()
{
	for(FConstControllerIterator It  = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASPGameModeBase::ResetOnePlayer(AController* Controller)
{
	if(IsValid(Controller) && IsValid(Controller->GetPawn()))
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASPGameModeBase::CreateTeamsInfo()
{
	int32 TeamID = 1;
	int32 BotCounter = 1;
	for(FConstControllerIterator It  = GetWorld()->GetControllerIterator(); It; ++It, BotCounter++)
	{
		AController* Controller = It->Get();
		if(IsValid(Controller))
		{
			ASPPlayerState* PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
			if(IsValid(PlayerState))
			{
				PlayerState->SetTeamID(TeamID);
				PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
				PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot" + FString::FromInt(BotCounter));
				SetPlayerColor(Controller);
				TeamID = TeamID == 1 ? 2 : 1;
			}
		}
	}
}

const FLinearColor& ASPGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if(TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	return GameData.DefaultTeamColor;
}

void ASPGameModeBase::SetPlayerColor(AController* Controller)
{
	if(IsValid(Controller))
	{
		ASPBaseCharacter* Character = Cast<ASPBaseCharacter>(Controller->GetPawn());
		if(IsValid(Character))
		{
			ASPPlayerState* PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
			Character->SetPlayerColor(PlayerState->GetTeamColor());
		}
	}
}

void ASPGameModeBase::LogPlayerInfo()
{
	for(FConstControllerIterator It  = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AController* Controller = It->Get();
		if(IsValid(Controller))
		{
			ASPPlayerState* PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
			if(IsValid(PlayerState))
			{
				PlayerState->LogInfo();
			}
		}
	}
}

void ASPGameModeBase::StartRespawn(AController* Controller)
{
	if(RoundCountDown > GameData.MinRoundTimeForRespawn + GameData.RespawnTime)
	{
		USPRespawnComponent* RespawnComponent = Controller->FindComponentByClass<USPRespawnComponent>();
		if(IsValid(RespawnComponent))
		{
			RespawnComponent->Respawn(GameData.RespawnTime);
		}
	}
}

void ASPGameModeBase::GameOver()
{
	LogPlayerInfo();

	for(APawn* Pawn : TActorRange<APawn>(GetWorld()))
	{
		if(IsValid(Pawn))
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(ESPMatchState::GameOver);
}

void ASPGameModeBase::SetMatchState(ESPMatchState State)
{
	if(CurrentMathState != State)
	{
		CurrentMathState = State;
		OnMathStateChanged.Broadcast(CurrentMathState);
	}
}
