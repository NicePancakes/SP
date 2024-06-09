#include "Menu/UI/SPMenuHUD.h"

#include "Blueprint/UserWidget.h"

void ASPMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	if(IsValid(MenuWidget))
	{
		MenuWidget->AddToViewport();
	}
}
