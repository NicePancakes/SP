#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SPGoToButtonWidget.generated.h"

UCLASS()
class SP_API USPGoToButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnButtonClickedEvent& GetOnButtonClickedEvent() { return GoToButton->OnClicked; }

	void GoToMap();
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnGoToButtonPressed();

	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GoToButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonText;

	UPROPERTY(EditAnywhere)
	FName GoToMapName = NAME_None;

	UPROPERTY(EditAnywhere)
	FText TextOnButton;

	UPROPERTY(EditAnywhere)
	bool bIsNeedDelegate = false;
	
};
