#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SPNextLocationTask.generated.h"


UCLASS()
class SP_API USPNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	USPNextLocationTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool bIsSelfCenter = true;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (EditCondition = "!bIsSelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
