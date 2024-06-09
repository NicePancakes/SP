#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPMenuPlayerController.generated.h"

UCLASS()
class SP_API ASPMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
