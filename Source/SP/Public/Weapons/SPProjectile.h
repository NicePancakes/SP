#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class USPWeaponFXComponent;

UCLASS()
class SP_API ASPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASPProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float SphereCollisionRadius = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USPWeaponFXComponent> WeaponFXComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	bool bDoFullDamage = false;

	UPROPERTY()
	FVector ShotDirection;
};
