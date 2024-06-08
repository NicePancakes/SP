#include "UI/PlayerHUDWidget.h"

#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UPlayerHUDWidget::Initialize()
{
	USPHealthComponent* HealthComponent = GetComponent<USPHealthComponent>();
	if(IsValid(HealthComponent))
	{
		HealthComponent->GetOnHealthChanged().AddUObject(this, &ThisClass::OnHealthChanged);
	}
	return Super::Initialize();
}

float UPlayerHUDWidget::GetHealthPercent() const
{
	USPHealthComponent* HealthComponent = GetComponent<USPHealthComponent>();
	if(IsValid(HealthComponent))
	{
		return HealthComponent->GetHealthPercent();
	}
	return 0.0f;
}

bool UPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	USPWeaponComponent* WeaponComponent = GetComponent<USPWeaponComponent>();
	if(IsValid(WeaponComponent))
	{
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}

bool UPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	//USPWeaponComponent* WeaponComponent = GetWeaponComponent();
	USPWeaponComponent* WeaponComponent = GetComponent<USPWeaponComponent>();
	if(IsValid(WeaponComponent))
	{
		return WeaponComponent->GetWeaponAmmoData(AmmoData);
	}

	return false;
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	USPHealthComponent* HealthComponent = GetComponent<USPHealthComponent>();
	return IsValid(HealthComponent) && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	AController* Controller = GetOwningPlayer();
	return IsValid(Controller) && Controller->GetStateName() == NAME_Spectating;
}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0)
	{
		OnTakeDamage();
	}
}
