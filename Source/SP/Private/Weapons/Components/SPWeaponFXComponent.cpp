#include "Weapons/Components/SPWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

USPWeaponFXComponent::USPWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponFXComponent::PlayImpactFX(const FHitResult& HitResults)
{
	FImpactData& ImpactData = DefaultImpactData;

	if(HitResults.PhysMaterial.IsValid())
	{
		UPhysicalMaterial* PhysMat = HitResults.PhysMaterial.Get();
		if(ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, HitResults.ImpactPoint, HitResults.ImpactNormal.Rotation());
	UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
		ImpactData.DecalData.Material, ImpactData.DecalData.Size, HitResults.ImpactPoint, HitResults.ImpactNormal.Rotation());

	if(IsValid(DecalComponent))
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, HitResults.ImpactPoint);
}

