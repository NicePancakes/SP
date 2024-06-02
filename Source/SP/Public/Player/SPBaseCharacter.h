#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SP_API ASPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPBaseCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	

};
