#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FDecalData DecalData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	USoundCue* Sound;
};

UCLASS()
class SP_API USPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	USPWeaponFXComponent();
		
	void PlayImpactFX(const FHitResult& HitResults);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TMap<TObjectPtr<UPhysicalMaterial>, FImpactData> ImpactDataMap;
};
