#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS()
class SP_API USPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	USPWeaponFXComponent();
		
	void PlayImpactFX(const FHitResult& HitResults);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> DefaultEffect;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TMap<TObjectPtr<UPhysicalMaterial>, TObjectPtr<UNiagaraSystem>> EffectsMap;
};
