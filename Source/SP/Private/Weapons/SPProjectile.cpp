#include "Weapons/SPProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Components/SPWeaponFXComponent.h"

ASPProjectile::ASPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(SphereCollisionRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USPWeaponFXComponent>(TEXT("WeaponFXComponent"));

	CollisionComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
}

void ASPProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);
	
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	SetLifeSpan(LifeTime);
}

void ASPProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), bDoFullDamage);
	WeaponFXComponent->PlayImpactFX(Hit);
	
	Destroy();
}

AController* ASPProjectile::GetController() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if(IsValid(Pawn))
	{
		return  Pawn->GetController();
	}
	return nullptr;
}
