#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SPGameHUD.generated.h"

UCLASS()
class SP_API ASPGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void DrawHUD() override;

	void DrawCrossHair();
	
};
