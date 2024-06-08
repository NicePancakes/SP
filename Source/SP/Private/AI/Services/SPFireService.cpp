#include "AI/Services/SPFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SPWeaponComponent.h"

USPFireService::USPFireService()
{
	NodeName = "Fire";
}

void USPFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	bool HasAim = IsValid(BlackboardComponent) && IsValid(BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName));

	if(IsValid(AIController))
	{
		USPWeaponComponent* WeaponComponent = AIController->GetPawn()->FindComponentByClass<USPWeaponComponent>();
		if(IsValid(WeaponComponent))
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StartFire();
		}
	}
}
