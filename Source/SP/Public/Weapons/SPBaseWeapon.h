#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo", meta = (EditCondition = "!bIsInfinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	bool bIsInfinite;
	
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

	FOnClipEmptySignature& GetOnClipEmptySignature() { return OnClipEmpty; }

protected:
	virtual void BeginPlay() override;

	virtual void MakeShot() {};
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void DecreaseAmmo();
	bool IsAmmoEmpty();
	bool IsClipEmpty();
	
	void LogAmmo();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly)
	float TraceLength = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo {};

	UPROPERTY()
	FAmmoData CurrentAmmo;

	FOnClipEmptySignature OnClipEmpty;
	
};
