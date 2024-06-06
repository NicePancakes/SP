#include "Components/SPWeaponComponent.h"
#include "Weapons/SPBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SPEquipFinishedAnimNotify.h"
#include "Animations/SPReloadFinishedAnimNotify.h"

USPWeaponComponent::USPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponComponent::StartFire()
{
	if(CanFire())
	{
		CurrentWeapon->StartFire();
	}
}

void USPWeaponComponent::StopFire()
{
	if(IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopFire();
	}
}

void USPWeaponComponent::NextWeapon()
{
	if(CanEquip())
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		EquipWeapon(CurrentWeaponIndex);
	}
}

void USPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == 2, TEXT("Character 2 wepon types"));
	
	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USPWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CurrentWeapon = nullptr;
	for(ASPBaseWeapon* Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
}

void USPWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(IsValid(Character))
	{
		for(const FWeaponData& OneWeaponData : WeaponData)
		{
			ASPBaseWeapon* Weapon = GetWorld()->SpawnActor<ASPBaseWeapon>(OneWeaponData.WeaponClass);
			if(IsValid(Weapon))
			{
				Weapon->GetOnClipEmptySignature().AddUObject(this, &USPWeaponComponent::OnEmptyClip);
				Weapon->SetOwner(Character);
				Weapons.Emplace(Weapon);

				AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
			}
		}
		
	}
}

void USPWeaponComponent::AttachWeaponToSocket(ASPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if(IsValid(Weapon) && IsValid(SceneComponent))
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	}
}

void USPWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(IsValid(Character))
	{
		if(IsValid(CurrentWeapon))
		{
			CurrentWeapon->StopFire();
			AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
		}
		
		CurrentWeapon = Weapons[WeaponIndex];
		FWeaponData* CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
		{
			return Data.WeaponClass == CurrentWeapon->GetClass();
		});
		CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
		
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
		bIsEquipAnimInProgress = true;
		PlayAnimMontage(EquipAnimMontage);
	}
}

void USPWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(IsValid(Character))
	{
		Character->PlayAnimMontage(AnimMontage);
	}
}

void USPWeaponComponent::InitAnimations()
{
	USPEquipFinishedAnimNotify* EquipFinishedAnimNotify = FindNotifyByClass<USPEquipFinishedAnimNotify>(EquipAnimMontage);
	if(IsValid(EquipFinishedAnimNotify))
	{
		EquipFinishedAnimNotify->GetOnNotifiedSignature().AddUObject(this, &USPWeaponComponent::OnEquipFinished);
	}
	else
	{
		checkNoEntry();
	}

	for(const FWeaponData& OneWeaponData : WeaponData)
	{
		USPReloadFinishedAnimNotify* ReloadFinishedAnimNotify = FindNotifyByClass<USPReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if(IsValid(ReloadFinishedAnimNotify))
		{
			ReloadFinishedAnimNotify->GetOnNotifiedSignature().AddUObject(this, &USPWeaponComponent::OnReloadFinished);
		}
		else
		{
			checkNoEntry();
		}
	}
}

void USPWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(IsValid(Character) || Character->GetMesh() == MeshComp)
	{
		bIsEquipAnimInProgress = false;
	}
}

void USPWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(IsValid(Character) || Character->GetMesh() == MeshComp)
	{
		bIsReloadAnimInProgress = false;
	}
}

bool USPWeaponComponent::CanFire() const
{
	return IsValid(CurrentWeapon) && !bIsEquipAnimInProgress && !bIsReloadAnimInProgress;
}

bool USPWeaponComponent::CanEquip() const
{
	return !bIsEquipAnimInProgress && !bIsReloadAnimInProgress;
}

bool USPWeaponComponent::CanReload() const
{
	return IsValid(CurrentWeapon)
			&& !bIsEquipAnimInProgress
			&& !bIsReloadAnimInProgress
			&& CurrentWeapon->CanReload();
}

void USPWeaponComponent::Reload()
{
	ChangeClip();
}

void USPWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void USPWeaponComponent::ChangeClip()
{
	if(CanReload())
	{
		CurrentWeapon->StopFire();
		CurrentWeapon->ChangeClip();
		bIsReloadAnimInProgress = true;
		PlayAnimMontage(CurrentReloadAnimMontage);
	}
}
