#include "AI/Services/SPChangeWeaponService.h"
#include "Components/SPWeaponComponent.h"
#include "AIController.h"

USPChangeWeaponService::USPChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USPChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if(IsValid(AIController))
	{
		//AActor* PlayerActor = AIController->GetPawn();
		//if(IsValid(PlayerActor))
		{
			USPWeaponComponent* WeaponComponent = AIController->GetPawn()->FindComponentByClass<USPWeaponComponent>();
			if(IsValid(WeaponComponent) && Probability > 0 &&  FMath::FRand() <= Probability)
			{
				WeaponComponent->NextWeapon();
			}
		}
		
	}
}
 