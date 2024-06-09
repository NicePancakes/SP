#include "Player/SPPlayerController.h"
#include "Components/SPRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASPPlayerController::ASPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>(TEXT("RespawnComponent"));
}

void ASPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(IsValid(InputComponent))
	{
		InputComponent->BindAction("PauseGame", IE_Pressed, this, &ThisClass::OnPauseGame);
	}
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ASPGameModeBase* GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		GameMode->GetOnMatchStateChangedSignature().AddUObject(this, &ThisClass::OnMatchStateChanged);
	}
}

void ASPPlayerController::OnPauseGame()
{
	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASPPlayerController::OnMatchStateChanged(ESPMatchState State)
{
	if(State == ESPMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
