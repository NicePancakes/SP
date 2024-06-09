#include "UI/SPGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "UI/PlayerHUDWidget.h"

void ASPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
	if(IsValid(PlayerHUDWidget))
	{
		PlayerHUDWidget->AddToViewport();
	}

	ASPGameModeBase* GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		GameMode->GetOnMathStateChangedSignature().AddUObject(this, &ThisClass::OnMatchStateChanged);
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

void ASPGameHUD::OnMatchStateChanged(ESPMathState State)
{
	UE_LOG(LogTemp, Error, TEXT("Math state changed: %s"), *UEnum::GetValueAsString(State))	
}
