#include "Weapons/SPLauncherWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Weapons/SPProjectile.h"

void ASPLauncherWeapon::StartFire()
{
	MakeShot();
	
}

void ASPLauncherWeapon::StopFire()
{
	
}

void ASPLauncherWeapon::MakeShot()
{
	FVector TraceStart;
	FVector TraceEnd;
	if(GetTraceData(TraceStart, TraceEnd) && !IsAmmoEmpty())
	{
		FHitResult HitResult;
		MakeHit(HitResult, TraceStart, TraceEnd);

		const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
		const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
		
		const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
		ASPProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASPProjectile>(ProjectileClass, SpawnTransform);
		if(IsValid(Projectile))
		{
			Projectile->SetShotDirection(Direction);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
		DecreaseAmmo();
	}
}
