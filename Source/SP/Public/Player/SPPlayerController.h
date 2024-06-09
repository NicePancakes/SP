#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditDefaultsOnly, Category  = "Components")
	TObjectPtr<USPRespawnComponent> RespawnComponent;
	
};
