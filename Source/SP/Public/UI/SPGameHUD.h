#pragma once

#include "CoreMinimal.h"
#include "SPGameModeBase.h"
#include "GameFramework/HUD.h"
#include "SPGameHUD.generated.h"

class UPlayerHUDWidget;

UCLASS()
class SP_API ASPGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	virtual void DrawHUD() override;

	void DrawCrossHair();

	void OnMatchStateChanged(ESPMatchState State);
;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentPlayerWidget;

	UPROPERTY()
	TMap<TEnumAsByte<ESPMatchState>, TObjectPtr<UUserWidget>> GameWidgets;
	
};
