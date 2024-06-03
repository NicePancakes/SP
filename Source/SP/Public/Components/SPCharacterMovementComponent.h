#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SPCharacterMovementComponent.generated.h"


UCLASS()
class SP_API USPCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 2.0f;
};
