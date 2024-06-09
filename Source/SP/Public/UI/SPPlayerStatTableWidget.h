#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPPlayerStatTableWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SP_API USPPlayerStatTableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNameText(const FText& Text);
	void SetKillsText(int32 KillsNum);
	void SetDeathText(int32 DeathNum);
	void SetTeamIDText(int32 TeamID);
	void SetPlayerIndicatorVisibility(bool bIsVisible);

protected:
	FText FormatFromIntToFText(int32 Num);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KillsText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DeathText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TeamIDText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PlayerIndicatorImage;
};
