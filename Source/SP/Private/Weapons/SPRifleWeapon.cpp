#include "Weapons/SPRifleWeapon.h"
#include "Engine/DamageEvents.h"
#include "Weapons/Components/SPWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
	InitMuzzleFX();
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
	MakeShot();
	bIsFirstShot = false;
}

void ASPRifleWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
	bIsFirstShot = true;
	SetMuzzleFXVisibility(false);
}

void ASPRifleWeapon::MakeShot()
{
	FVector TraceStart;
	FVector TraceEnd;
	if(GetTraceData(TraceStart, TraceEnd) && !IsAmmoEmpty())
	{
		FHitResult HitResult;
		MakeHit(HitResult, TraceStart, TraceEnd);

		FVector TraceFXEnd = TraceEnd;
		if(HitResult.bBlockingHit)
		{
			TraceFXEnd = HitResult.ImpactPoint;
			MakeDamage(HitResult);
			WeaponFXComponent->PlayImpactFX(HitResult);
		}
		SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
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

void ASPRifleWeapon::InitMuzzleFX()
{
	if(!IsValid(MuzzleFXComponent))
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void ASPRifleWeapon::SetMuzzleFXVisibility(bool bIsVisible)
{
	if(IsValid(MuzzleFXComponent))
	{
		MuzzleFXComponent->SetPaused(!bIsVisible);
		MuzzleFXComponent->SetVisibility(bIsVisible);
	}
}

void ASPRifleWeapon::SpawnTraceFX(const FVector& StartTrace, const FVector& EndTrace)
{
	UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, StartTrace);
	if(IsValid(TraceFXComponent))
	{
		TraceFXComponent->SetVariableVec3(TraceTargetName, EndTrace);
	}
}


