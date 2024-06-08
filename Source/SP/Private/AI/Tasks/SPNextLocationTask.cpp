#include "AI/Tasks/SPNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USPNextLocationTask::USPNextLocationTask()
{
	NodeName = "Find Next Location";
}

EBTNodeResult::Type USPNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if(IsValid(Controller) && IsValid(Blackboard))
	{
		APawn* Pawn = Controller->GetPawn();
		if(IsValid(Pawn))
		{
			auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
			if(IsValid(NavSystem))
			{
				FNavLocation NavLocation;
				FVector Location = Pawn->GetActorLocation();
				if(!bIsSelfCenter)
				{
					AActor* CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
					if(IsValid(CenterActor))
					{
						Location = CenterActor->GetActorLocation();
					}
					else
					{
						return EBTNodeResult::Failed;
					}
				}
				if(NavSystem->GetRandomReachablePointInRadius(Location, Radius, NavLocation))
				{
					Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
