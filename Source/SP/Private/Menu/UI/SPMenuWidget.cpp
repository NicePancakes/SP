#include "Menu/UI/SPMenuWidget.h"

#include "SPGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USPMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartGameButton->GetOnButtonClickedEvent().RemoveAll(this);
	StartGameButton->GetOnButtonClickedEvent().AddDynamic(this, &ThisClass::OnStartGameButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnExitButtonPressed);
}

void USPMenuWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USPMenuWidget::OnStartGameButtonPressed()
{
	PlayAnimation(HideAnimation);
}

void USPMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation == HideAnimation)
	{
		StartGameButton->GoToMap();
	}
}
