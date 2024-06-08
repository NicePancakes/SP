#pragma once

#include "CoreMinimal.h"
#include "Components/SPWeaponComponent.h"
#include "SPAIWeaponComponent.generated.h"


UCLASS()
class SP_API USPAIWeaponComponent : public USPWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
};
