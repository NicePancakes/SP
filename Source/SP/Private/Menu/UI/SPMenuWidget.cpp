#include "Menu/UI/SPMenuWidget.h"

#include "SPGameInstance.h"
#include "SPGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void USPMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartGameButton->GetOnButtonClickedEvent().RemoveAll(this);
	StartGameButton->GetOnButtonClickedEvent().AddDynamic(this, &ThisClass::OnStartGameButtonPressed);
	ExitButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnExitButtonPressed);
	PlayerCountEditableTextBox->OnTextChanged.AddUniqueDynamic(this, &ThisClass::OnTextChanged);

	PlayerCountEditableTextBox->SetForegroundColor(FLinearColor::White);
}

void USPMenuWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USPMenuWidget::OnStartGameButtonPressed()
{
	if(!PlayerCountEditableTextBox->GetText().IsEmpty())
	{
		int32 PlayerCounts = FCString::Atoi(*PlayerCountEditableTextBox->GetText().ToString());
		USPGameInstance* GameInstance = Cast<USPGameInstance>(GetGameInstance());
		if(IsValid(GameInstance))
		{
			GameInstance->SetPlayerCounts(PlayerCounts);
		}
		
		PlayAnimation(HideAnimation);
	}
	else
	{
		PlayerCountEditableTextBox->SetForegroundColor(FLinearColor::Red);
	}
}

void USPMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation == HideAnimation)
	{
		StartGameButton->GoToMap();
	}
}

void USPMenuWidget::OnTextChanged(const FText& Text)
{
	PlayerCountEditableTextBox->SetForegroundColor(FLinearColor::White);
	if(!Text.IsNumeric())
	{
		FString TextString = Text.ToString();
		PlayerCountEditableTextBox->SetText(FText::FromString(TextString.LeftChop(1)));
	}
}
