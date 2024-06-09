#include "UI/SPGoToButtonWidget.h"

#include "Kismet/GameplayStatics.h"

void USPGoToButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(bIsNeedDelegate)
	{
		GoToButton->OnClicked.AddDynamic(this, &ThisClass::USPGoToButtonWidget::OnGoToButtonPressed);
	}
	ButtonText->SetText(TextOnButton);
}

void USPGoToButtonWidget::GoToMap()
{
	if(!GoToMapName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, GoToMapName);
	}
}

void USPGoToButtonWidget::OnGoToButtonPressed()
{
	GoToMap();
}
