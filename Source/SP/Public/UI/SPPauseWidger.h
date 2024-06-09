#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SPPauseWidger.generated.h"


UCLASS()
class SP_API USPPauseWidger : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnContinueButtonPressed();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
};
