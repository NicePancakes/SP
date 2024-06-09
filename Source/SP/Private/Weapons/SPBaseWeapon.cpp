#include "Weapons/SPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASPBaseWeapon::ASPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(RootComponent);
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void ASPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Incrorrect count of bullets, bullest couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Incrorrect count of clips, clips couldn't be less or equal zero"));

	CurrentAmmo = DefaultAmmo;
}

bool ASPBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if(!IsValid(PlayerCharacter)) return false;
	
	if(PlayerCharacter->IsPlayerControlled())
	{
		APlayerController* PlayerController =  PlayerCharacter->GetController<APlayerController>();
		if(!IsValid(PlayerController)) return false;
		
		PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
	return true;
}

FVector ASPBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASPBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		TraceStart = ViewLocation;
		const FVector ShotDirection = ViewRotation.Vector();
		TraceEnd = TraceStart + ShotDirection * TraceLength;
		return true;
	}
	return false;
}

void ASPBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);
}

void ASPBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets > 0)
	{
		CurrentAmmo.Bullets--;
	}
	
	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool ASPBaseWeapon::IsAmmoEmpty()
{
	return !CurrentAmmo.bIsInfinite && CurrentAmmo.Clips == 0 && IsClipEmpty(); 
}

bool ASPBaseWeapon::IsClipEmpty()
{
	return CurrentAmmo.Bullets == 0;
}

UNiagaraComponent* ASPBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
		WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

void ASPBaseWeapon::ChangeClip()
{
	if(!CurrentAmmo.bIsInfinite && CurrentAmmo.Clips > 0)
	{
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ASPBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}
