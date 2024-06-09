#include "Player/SPPlayerState.h"

void ASPPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("Team ID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
