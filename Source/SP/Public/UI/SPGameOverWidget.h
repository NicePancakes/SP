#pragma once

#include "CoreMinimal.h"
#include "SPGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "SPGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SP_API USPGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	void OnMatchStateChanged(ESPMatchState State);
	void UpdatePlayersStat();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatTableWidgetClass;
	
};
