#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SPMenuHUD.generated.h"


UCLASS()
class SP_API ASPMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	
};
