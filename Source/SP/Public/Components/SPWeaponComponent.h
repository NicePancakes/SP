#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/SPBaseWeapon.h"
#include "SPWeaponComponent.generated.h"

class ASPBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASPBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> ReloadAnimMontage;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API USPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USPWeaponComponent();

	virtual void StartFire();
	virtual void NextWeapon();
	void StopFire();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();
	
	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if(IsValid(Animation))
		{
			TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;
			for(FAnimNotifyEvent NotifyEvent : NotifyEvents)
			{
				T* AnimNotify = Cast<T>(NotifyEvent.Notify);
				if(IsValid(AnimNotify))
				{
					return AnimNotify;
				}
			}
		}
		return nullptr;
	}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY()
	TObjectPtr<ASPBaseWeapon> CurrentWeapon;

	UPROPERTY()
	TObjectPtr<UAnimMontage> CurrentReloadAnimMontage;

	UPROPERTY()
	TArray<TObjectPtr<ASPBaseWeapon>> Weapons;

	int32 CurrentWeaponIndex = 0;
	bool bIsEquipAnimInProgress = false;
	bool bIsReloadAnimInProgress = false;
};
