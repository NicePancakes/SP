#include "UI/SPPauseWidger.h"
#include "SPGameModeBase.h"

void USPPauseWidger::NativeConstruct()
{
	Super::NativeConstruct();
	ContinueButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnContinueButtonPressed);
}

void USPPauseWidger::NativeDestruct()
{
	Super::NativeDestruct();

	ContinueButton->OnClicked.RemoveAll(this);
}

void USPPauseWidger::OnContinueButtonPressed()
{
	if(IsValid(GetWorld()->GetAuthGameMode()))
	{
		GetWorld()->GetAuthGameMode()->ClearPause();
	}
}
