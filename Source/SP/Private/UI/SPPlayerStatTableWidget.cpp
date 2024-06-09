#include "UI/SPPlayerStatTableWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USPPlayerStatTableWidget::SetNameText(const FText& Text)
{
	NameText->SetText(Text);
}

void USPPlayerStatTableWidget::SetKillsText(int32 KillsNum)
{
	KillsText->SetText(FormatFromIntToFText(KillsNum));
}

void USPPlayerStatTableWidget::SetDeathText(int32 DeathNum)
{
	DeathText->SetText(FormatFromIntToFText(DeathNum));
}

void USPPlayerStatTableWidget::SetTeamIDText(int32 TeamID)
{
	TeamIDText->SetText(FormatFromIntToFText(TeamID));
}

void USPPlayerStatTableWidget::SetPlayerIndicatorVisibility(bool bIsVisible)
{
	PlayerIndicatorImage->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

FText USPPlayerStatTableWidget::FormatFromIntToFText(int32 Num)
{
	return FText::FromString(FString::FromInt(Num));
}
