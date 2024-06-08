#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SPChangeWeaponService.generated.h"


UCLASS()
class SP_API USPChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	USPChangeWeaponService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5f;
};
