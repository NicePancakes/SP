#include "UI/SPGameOverWidget.h"

#include "Components/Button.h"
#include "Player/SPPlayerState.h"
#include "UI/SPPlayerStatTableWidget.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void USPGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ASPGameModeBase* GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		GameMode->GetOnMatchStateChangedSignature().AddUObject(this, &ThisClass::OnMatchStateChanged);
	}
}

void USPGameOverWidget::OnMatchStateChanged(ESPMatchState State)
{
	if(State == ESPMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USPGameOverWidget::UpdatePlayersStat()
{
	PlayerStatBox->ClearChildren();
	for(FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AController* Controller = It->Get();
		if(!IsValid(Controller)) return;

		ASPPlayerState* PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
		if(!IsValid(PlayerState)) return;

		USPPlayerStatTableWidget* PlayerStatTableWidget = CreateWidget<USPPlayerStatTableWidget>(GetWorld(), PlayerStatTableWidgetClass);
		if(!IsValid(PlayerStatTableWidget)) return;

		PlayerStatTableWidget->SetNameText(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatTableWidget->SetKillsText(PlayerState->GetKillsNum());
		PlayerStatTableWidget->SetDeathText(PlayerState->GetKillsNum());
		PlayerStatTableWidget->SetTeamIDText(PlayerState->GetKillsNum());
		PlayerStatTableWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatTableWidget);
	}
}
