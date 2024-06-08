#include "Components/SPHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"

USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);
	SetHealth(MaxHealth);

	AActor* Owner = GetOwner();
	if(IsValid(Owner))
	{
		Owner->OnTakeAnyDamage.AddUniqueDynamic(this, &ThisClass::OnTakeAnyDamage);
	}
}

void USPHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || CurrentHealth <=0.0f) { return; }

	SetHealth(CurrentHealth - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &ThisClass::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
}

void USPHealthComponent::HealUpdate()
{
	SetHealth(CurrentHealth + HealModifier);

	if(FMath::IsNearlyEqual(CurrentHealth, MaxHealth))
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USPHealthComponent::SetHealth(float Health)
{
	float NewHealth = FMath::Clamp(Health, 0.0f, MaxHealth);
	float HealthDelta = NewHealth - CurrentHealth;
	CurrentHealth = NewHealth;
	OnHealthChanged.Broadcast(CurrentHealth, HealthDelta);
}

void USPHealthComponent::PlayCameraShake()
{
	APawn* Player = Cast<APawn>(GetOwner());
	if(IsValid(Player) && !IsDead())
	{
		APlayerController* Controller = Player->GetController<APlayerController>();
		if(IsValid(Controller) && IsValid(Controller->PlayerCameraManager))
		{
			Controller->PlayerCameraManager->StartCameraShake(CameraShake);
		}
	}
}
