#pragma once

#include "CoreMinimal.h"
#include "Weapons/SPBaseWeapon.h"
#include "SPRifleWeapon.generated.h"

class USPWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundCue;

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

	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool bIsVisible);
	void SpawnTraceFX(const FVector& StartTrace, const FVector& EndTrace);
	AController* GetController() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 10.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> TraceFX;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FName TraceTargetName = "TraceTarget";

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<USPWeaponFXComponent> WeaponFXComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UAudioComponent> FireAudioComponent;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> MuzzleFXComponent;

	bool bIsFirstShot = true;

	FTimerHandle ShotTimerHandle;
};
