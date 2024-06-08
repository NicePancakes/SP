#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SPFireService.generated.h"

UCLASS()
class SP_API USPFireService : public UBTService
{
	GENERATED_BODY()

public:
	USPFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	
};
