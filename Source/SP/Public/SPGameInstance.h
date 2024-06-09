#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SPGameInstance.generated.h"


UCLASS()
class SP_API USPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const FName& GetStartupLevelName() const { return StartupLevelName; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;
	
};
