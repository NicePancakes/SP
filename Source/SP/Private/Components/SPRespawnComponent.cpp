#include "Components/SPRespawnComponent.h"
#include "SPGameModeBase.h"


USPRespawnComponent::USPRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPRespawnComponent::Respawn(int32 RespawnTime)
{
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::RespawnTimerUpdate, 1.0f, true);
}

bool USPRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USPRespawnComponent::RespawnTimerUpdate()
{
	if(--RespawnCountDown == 0)
	{
		ASPGameModeBase* GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
		if(IsValid(GameMode))
		{
			GameMode->RespawnRequest(Cast<AController>(GetOwner()));
		}
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	}
}


