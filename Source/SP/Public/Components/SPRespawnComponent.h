#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API USPRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USPRespawnComponent();

	void Respawn(int32 RespawnTime);

	int32 GetRespawnCountDown() const { return RespawnCountDown; }
	bool IsRespawnInProgress() const;
	
protected:
	void RespawnTimerUpdate();

protected:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;
};
