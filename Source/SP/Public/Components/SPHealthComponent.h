#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API USPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FOnDeath)
	DECLARE_DELEGATE_OneParam(FOnHealthChanged, float)

public:	
	USPHealthComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(CurrentHealth); }

	float GetCurrentHealth() const { return CurrentHealth;}
	FOnDeath& GetOnDeath() { return OnDeath; }
	FOnHealthChanged& GetOnHealthChanged() { return OnHealthChanged; }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate();
	void SetHealth(float NewHealth);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	bool AutoHeal = false;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;
	
	float CurrentHealth = 0.0f;

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	FTimerHandle HealTimerHandle;
};
