#include "SPGameModeBase.h"

#include "Player/SPBaseCharacter.h"
#include "Player/SPPlayerController.h"

ASPGameModeBase::ASPGameModeBase()
{
	DefaultPawnClass = ASPBaseCharacter::StaticClass();
	PlayerControllerClass = ASPPlayerController::StaticClass();
}
