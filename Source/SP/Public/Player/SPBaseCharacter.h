#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPBaseCharacter.generated.h"

class UTextRenderComponent;
class USpringArmComponent;
class UCameraComponent;
class USPHealthComponent;

UCLASS()
class SP_API ASPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnHealthChanged(float NewHealth);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USPHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UTextRenderComponent> HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "")
	float LifeTime = 5.0f;
	
	
	bool IsWantRun = false;
	bool IsMoveForward = false;
};
