#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!bIsInfinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	bool bIsInfinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTexture2D> MainWeaponIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTexture2D> CrossHairWeaponIcon;
};

UCLASS()
class SP_API ASPBaseWeapon : public AActor
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)
	
public:	
	ASPBaseWeapon();
	
	virtual void StartFire() {};
	virtual void StopFire() {};

	void ChangeClip();
	bool CanReload() const;
	bool IsAmmoEmpty();

	FOnClipEmptySignature& GetOnClipEmptySignature() { return OnClipEmpty; }
	FWeaponUIData& GetUIData() { return UIData; }
	FAmmoData& GetAmmoData() { return CurrentAmmo; }

protected:
	virtual void BeginPlay() override;

	virtual void MakeShot() {};
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void DecreaseAmmo();
	bool IsClipEmpty();

	UNiagaraComponent* SpawnMuzzleFX();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly)
	float TraceLength = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY()
	FAmmoData CurrentAmmo;

	FOnClipEmptySignature OnClipEmpty;
};
