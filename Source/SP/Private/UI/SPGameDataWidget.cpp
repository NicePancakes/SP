#include "UI/SPGameDataWidget.h"
#include "SPGameModeBase.h"
#include "Player/SPPlayerState.h"

int32 USPGameDataWidget::GetKillsNum() const
{
	ASPPlayerState* PlayerState = GetPlayerState();
	return IsValid(PlayerState) ? PlayerState->GetKillsNum() : 0;
}

int32 USPGameDataWidget::GetDeathsNum() const
{
	ASPPlayerState* PlayerState = GetPlayerState();
	return IsValid(PlayerState) ? PlayerState->GetDeathsNum() : 0;
}

int32 USPGameDataWidget::GetCurrentRoundNum() const
{
	ASPGameModeBase* GameMode = GetGameMode();
	return IsValid(GameMode) ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USPGameDataWidget::GetTotalRoundsNum() const
{
	ASPGameModeBase* GameMode = GetGameMode();
	return IsValid(GameMode) ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USPGameDataWidget::GetRoundSecondsRemaining() const
{
	ASPGameModeBase* GameMode = GetGameMode();
	return IsValid(GameMode) ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASPGameModeBase* USPGameDataWidget::GetGameMode() const
{
	return Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
}

ASPPlayerState* USPGameDataWidget::GetPlayerState() const
{
	return IsValid(GetOwningPlayer()) ? Cast<ASPPlayerState>(GetOwningPlayer()->PlayerState) : nullptr; 
}
