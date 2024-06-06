#include "Weapons/SPProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASPProjectile::ASPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(SphereCollisionRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	CollisionComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
}

void ASPProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	SetLifeSpan(LifeTime);
}

void ASPProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), bDoFullDamage);
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 32, FColor::Red, false, 5.0f, 0, 3.0f);
	
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
