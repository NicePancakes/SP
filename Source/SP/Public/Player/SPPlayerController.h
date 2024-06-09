#pragma once

#include "CoreMinimal.h"
#include "SPGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

class USPRespawnComponent;

UCLASS()
class SP_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASPPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	void OnPauseGame();
	void OnMatchStateChanged(ESPMatchState State);

protected:
	UPROPERTY(EditDefaultsOnly, Category  = "Components")
	TObjectPtr<USPRespawnComponent> RespawnComponent;
	
};
