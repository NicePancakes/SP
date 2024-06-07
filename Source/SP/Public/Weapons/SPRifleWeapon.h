#pragma once

#include "CoreMinimal.h"
#include "Weapons/SPBaseWeapon.h"
#include "SPRifleWeapon.generated.h"

class USPWeaponFXComponent;

UCLASS()
class SP_API ASPRifleWeapon : public ASPBaseWeapon
{
	GENERATED_BODY()

public:
	ASPRifleWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	void MakeDamage(const FHitResult& HitResult);

protected:
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 10.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpread = 1.5f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USPWeaponFXComponent> WeaponFXComponent;

	bool bIsFirstShot = true;

	FTimerHandle ShotTimerHandle;
};
