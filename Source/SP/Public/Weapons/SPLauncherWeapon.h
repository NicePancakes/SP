#pragma once

#include "CoreMinimal.h"
#include "Weapons/SPBaseWeapon.h"
#include "SPLauncherWeapon.generated.h"

class ASPProjectile;

UCLASS()
class SP_API ASPLauncherWeapon : public ASPBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASPProjectile> ProjectileClass;
};
