#include "Components/SPAIWeaponComponent.h"
#include "Weapons/SPBaseWeapon.h"

void USPAIWeaponComponent::StartFire()
{
	if(CanFire())
	{
		if(CurrentWeapon->IsAmmoEmpty())
		{
			NextWeapon();
		}
		else
		{
			CurrentWeapon->StartFire();
		}
	}
}

void USPAIWeaponComponent::NextWeapon()
{
	if(CanEquip())
	{
		int32 NewPossibleWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		while (NewPossibleWeaponIndex != CurrentWeaponIndex)
		{
			if(!Weapons[NewPossibleWeaponIndex]->IsAmmoEmpty())
			{
				break;
			}
			NewPossibleWeaponIndex = (NewPossibleWeaponIndex + 1) % Weapons.Num();
		}

		if(CurrentWeaponIndex != NewPossibleWeaponIndex)
		{
			CurrentWeaponIndex = NewPossibleWeaponIndex;
			EquipWeapon(CurrentWeaponIndex);
		}
	}
}
