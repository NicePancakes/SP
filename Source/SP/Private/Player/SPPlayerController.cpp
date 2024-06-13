#include "Player/SPPlayerController.h"

#include "SPGameInstance.h"
#include "Components/SPRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASPPlayerController::ASPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>(TEXT("RespawnComponent"));
}

void ASPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USPGameInstance* GameInstance = Cast<USPGameInstance>(GetGameInstance());
	if(IsValid(GameInstance))
	{
		if(GameInstance->GetIsLeftHandMode())
		{
			if(IsValid(InputComponent))
			{
				InputComponent->BindAction("PauseGameLeftMode", IE_Pressed, this, &ThisClass::OnPauseGame);
			}
		}
		else
		{
			if(IsValid(InputComponent))
			{
				InputComponent->BindAction("PauseGame", IE_Pressed, this, &ThisClass::OnPauseGame);
			}
		}
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
