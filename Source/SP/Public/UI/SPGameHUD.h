#pragma once

#include "CoreMinimal.h"
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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUDWidget> PlayerHUDWidget;
	
};
