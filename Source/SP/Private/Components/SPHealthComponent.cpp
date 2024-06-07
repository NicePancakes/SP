#include "Components/SPHealthComponent.h"

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
	OnHealthChanged.Broadcast(CurrentHealth);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &ThisClass::HealUpdate, HealUpdateTime, true, HealDelay);
	}
}

void USPHealthComponent::HealUpdate()
{
	SetHealth(CurrentHealth + HealModifier);
	OnHealthChanged.Broadcast(CurrentHealth);

	if(FMath::IsNearlyEqual(CurrentHealth, MaxHealth))
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USPHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}
