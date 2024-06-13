#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "UI/SPGoToButtonWidget.h"
#include "Components/EditableTextBox.h"
#include "SPMenuWidget.generated.h"

UCLASS()
class SP_API USPMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnExitButtonPressed();

	UFUNCTION()
	void OnStartGameButtonPressed();

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UFUNCTION()
	void OnTextChanged(const FText& Text);

	UFUNCTION()
	void OnCheckStateChanged(bool bIsChecked);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USPGoToButtonWidget> StartGameButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> PlayerCountEditableTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> LeftHandModeCheckBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TutorialTextBlock;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HideAnimation;

	FText RightHandTextTip = FText::FromString(TEXT("To move forward use W\nTo move backward use S\nTo move left use A\nTo move right use D\nTo fire use Rifght Mouse Button\nTo reload use R\nTo open pause menu use Escape"));
	FText LeftHandTextTip = FText::FromString(TEXT("To move forward use ↑\nTo move backward use ↓\nTo move left use ←\nTo move right use →\nTo fire use Rifght Mouse Button\nTo reload use Enter\nTo open pause menu use P"));
};
