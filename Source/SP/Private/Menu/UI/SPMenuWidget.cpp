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
	LeftHandModeCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &ThisClass::OnCheckStateChanged);

	PlayerCountEditableTextBox->SetForegroundColor(FLinearColor::White);
	TutorialTextBlock->SetText(RightHandTextTip);
}

void USPMenuWidget::OnExitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USPMenuWidget::OnStartGameButtonPressed()
{
	int32 PlayerCounts = FCString::Atoi(*PlayerCountEditableTextBox->GetText().ToString());
	if(!PlayerCountEditableTextBox->GetText().IsEmpty() && PlayerCounts > 0)
	{
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
		PlayerCountEditableTextBox->SetText(FText::FromString(TEXT("")));
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

void USPMenuWidget::OnCheckStateChanged(bool bIsChecked)
{
	USPGameInstance* GameInstance = Cast<USPGameInstance>(GetGameInstance());
	if(IsValid(GameInstance))
	{
		GameInstance->SetIsLeftHandMode(bIsChecked);
	}

	if(bIsChecked)
	{
		TutorialTextBlock->SetText(LeftHandTextTip);
	}
	else
	{
		TutorialTextBlock->SetText(RightHandTextTip);
	}
}
