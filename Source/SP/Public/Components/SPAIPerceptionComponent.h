#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SPAIPerceptionComponent.generated.h"


class ASPPlayerState;

UCLASS()
class SP_API USPAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestEnemy() const;

protected:
	bool CheckHostility(AController* Controller1, AController* Controller2) const;
	
};
