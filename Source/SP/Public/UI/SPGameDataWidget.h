#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPGameDataWidget.generated.h"


class ASPGameModeBase;
class ASPPlayerState;

UCLASS()
class SP_API USPGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetDeathsNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

protected:
	ASPGameModeBase* GetGameMode() const;
	ASPPlayerState* GetPlayerState() const;
	
};
