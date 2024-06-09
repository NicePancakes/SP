#include "Player/SPPlayerController.h"
#include "Components/SPRespawnComponent.h"

ASPPlayerController::ASPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>(TEXT("RespawnComponent"));
}
