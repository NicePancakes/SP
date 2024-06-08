#include "AI/Services/SPFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SPAIPerceptionComponent.h"

USPFindEnemyService::USPFindEnemyService()
{
	NodeName = "FindEnemy";
}

void USPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(IsValid(BlackboardComponent))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		USPAIPerceptionComponent* AIPerceptionComponent = AIController->FindComponentByClass<USPAIPerceptionComponent>();
		if(IsValid(AIPerceptionComponent))
		{
			BlackboardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetClosestEnemy());
		}
	}
}
