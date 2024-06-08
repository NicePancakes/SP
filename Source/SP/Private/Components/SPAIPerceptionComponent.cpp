#include "Components/SPAIPerceptionComponent.h"
#include "AI/SPAIController.h"
#include "Components/SPHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USPAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

	if(PercieveActors.Num() == 0) return nullptr;

	AAIController* AIController = Cast<AAIController>(GetOwner());
	if(!IsValid(AIController)) return nullptr;

	APawn* Pawn = AIController->GetPawn();
	if(!IsValid(Pawn)) return nullptr;
	
	float BestDistance = MAX_FLT;
	AActor* ClosestEnemy = nullptr;
	for(AActor* Actor : PercieveActors)
	{
		USPHealthComponent* HealthComponent = Actor->FindComponentByClass<USPHealthComponent>();
		if(IsValid(HealthComponent) && !HealthComponent->IsDead())
		{
			float CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if(BestDistance > CurrentDistance)
			{
				BestDistance = CurrentDistance;
				ClosestEnemy = Actor;
			}
		}
	}
	return ClosestEnemy;
}
