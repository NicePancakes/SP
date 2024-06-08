#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Weapons/SPBaseWeapon.h"
#include "PlayerHUDWidget.generated.h"


class USPHealthComponent;
class USPWeaponComponent;
class UImage;
struct FWeaponUIData;
class UProgressBar;

UCLASS()
class SP_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable,Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

protected:

	virtual bool Initialize() override;

	void OnHealthChanged(float Health, float HealthDelta);
	
	template<typename T>
	T* GetComponent() const
	{
		APawn* Player = GetOwningPlayerPawn();
		if(IsValid(Player))
		{
			T* Component = Cast<T>(Player->GetComponentByClass(T::StaticClass()));
			if(IsValid(Component))
			{
				return Component;
			}
		}
		return nullptr;
	}
};
