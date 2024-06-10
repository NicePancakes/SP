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

// void USPGameOverWidget::SortByKills()
// {
// 	TArray<USPPlayerStatTableWidget*> WidgetsTable;
//
// 	int32 CurrentMaxKills = 0;
// 	int32 TopPlayerIdx = 0;
// 	for(int32 i = 0; i < PlayerStatBox->GetChildrenCount(); i++)
// 	{
// 		for(int32 j = i; j < PlayerStatBox->GetChildrenCount(); j++)
// 		{
// 			USPPlayerStatTableWidget* Widget = Cast<USPPlayerStatTableWidget>(PlayerStatBox->GetAllChildren()[i]);
// 			if(Widget->GetKillNums() > CurrentMaxKills)
// 			{
// 				CurrentMaxKills = Widget->GetKillNums();
// 				TopPlayerIdx = j;
// 			}
// 		}
// 		USPPlayerStatTableWidget* Widget = Cast<USPPlayerStatTableWidget>(PlayerStatBox->GetAllChildren()[TopPlayerIdx]);
// 		WidgetsTable.Add(Widget);
// 		
// 		CurrentMaxKills = 0;
// 		TopPlayerIdx = 0;
// 	}
//
// 	PlayerStatBox->ClearChildren();
// 	for(USPPlayerStatTableWidget* Widget : WidgetsTable)
// 	{
// 		PlayerStatBox->AddChild(Widget);
// 	}
// }
