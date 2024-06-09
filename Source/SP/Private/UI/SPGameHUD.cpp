#include "UI/SPGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "UI/PlayerHUDWidget.h"

void ASPGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GameWidgets.Emplace(ESPMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Emplace(ESPMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Emplace(ESPMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for(const TPair<ESPMatchState, TObjectPtr<UUserWidget>>& GameWidgetPair : GameWidgets)
	{
		GameWidgetPair.Value->AddToViewport();
		GameWidgetPair.Value->SetVisibility(ESlateVisibility::Hidden);
	}

	ASPGameModeBase* GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		GameMode->GetOnMatchStateChangedSignature().AddUObject(this, &ThisClass::OnMatchStateChanged);
	}
}

void ASPGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void ASPGameHUD::DrawCrossHair()
{
	TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASPGameHUD::OnMatchStateChanged(ESPMatchState State)
{
	if(IsValid(CurrentPlayerWidget))
	{
		CurrentPlayerWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GameWidgets.Contains(State))
	{
		CurrentPlayerWidget = GameWidgets[State];
		CurrentPlayerWidget->SetVisibility(ESlateVisibility::Visible);
	}
	UE_LOG(LogTemp, Error, TEXT("Math state changed: %s"), *UEnum::GetValueAsString(State))	
}
