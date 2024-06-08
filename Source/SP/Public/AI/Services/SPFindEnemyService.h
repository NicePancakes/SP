#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SPFindEnemyService.generated.h"


UCLASS()
class SP_API USPFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USPFindEnemyService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	
};
