#include "Weapons/SPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


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

APlayerController* ASPBaseWeapon::GetPlayerController() const
{
	const ACharacter* Player = Cast<ACharacter>(GetOwner());
	if(IsValid(Player))
	{
		APlayerController* Controller = Player->GetController<APlayerController>();
		if(IsValid(Controller))
		{
			return Controller;
		}
		return nullptr;
	}
	return nullptr;
}

bool ASPBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	APlayerController* PlayerController = GetPlayerController();
	if(IsValid(PlayerController))
	{
		PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
		return true;
	}
	return false;
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
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
}

void ASPBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets > 0)
	{
		CurrentAmmo.Bullets--;
	}
	LogAmmo();
	
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

void ASPBaseWeapon::ChangeClip()
{
	if(!CurrentAmmo.bIsInfinite && CurrentAmmo.Clips > 0)
	{
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogTemp, Error, TEXT("--------------Change clip--------------"));
}

bool ASPBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void ASPBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.bIsInfinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *AmmoInfo);
}
