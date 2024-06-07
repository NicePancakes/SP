#include "Weapons/SPRifleWeapon.h"
#include "Engine/DamageEvents.h"
#include "Weapons/Components/SPWeaponFXComponent.h"

ASPRifleWeapon::ASPRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USPWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

void ASPRifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponFXComponent);
}

void ASPRifleWeapon::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
	MakeShot();
	bIsFirstShot = false;
}

void ASPRifleWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
	bIsFirstShot = true;
}

void ASPRifleWeapon::MakeShot()
{
	FVector TraceStart;
	FVector TraceEnd;
	if(GetTraceData(TraceStart, TraceEnd) && !IsAmmoEmpty())
	{
		FHitResult HitResult;
		MakeHit(HitResult, TraceStart, TraceEnd);
		
		if(HitResult.bBlockingHit)
		{
			MakeDamage(HitResult);
			WeaponFXComponent->PlayImpactFX(HitResult);
		}
		else
		{
			DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
		}
		DecreaseAmmo();
	}
	else
	{
		StopFire();
	}
}

bool ASPRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		TraceStart = ViewLocation;
		const float HalfRad = FMath::DegreesToRadians(BulletSpread);
		const FVector ShotDirection = bIsFirstShot ? ViewRotation.Vector() : FMath::VRandCone(ViewRotation.Vector(), HalfRad);
		TraceEnd = TraceStart + ShotDirection * TraceLength;
		return true;
	}
	return false;
}

void ASPRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* DamageActor = HitResult.GetActor();
	if(IsValid(DamageActor))
	{
		DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
	}
}


