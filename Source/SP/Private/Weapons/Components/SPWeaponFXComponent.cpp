#include "Weapons/Components/SPWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


USPWeaponFXComponent::USPWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponFXComponent::PlayImpactFX(const FHitResult& HitResults)
{
	UNiagaraSystem* Effect = DefaultEffect;

	if(HitResults.PhysMaterial.IsValid())
	{
		UPhysicalMaterial* PhysMat = HitResults.PhysMaterial.Get();
		if(EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResults.ImpactPoint, HitResults.ImpactNormal.Rotation());
}

