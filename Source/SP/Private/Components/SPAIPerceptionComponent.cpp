#include "Components/SPAIPerceptionComponent.h"
#include "AI/SPAIController.h"
#include "Components/SPHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/SPPlayerState.h"

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
		APawn* PercievePawn = Cast<APawn>(Actor);
		bool AreEnemies = IsValid(PercievePawn) && CheckHostility(AIController, PercievePawn->Controller);
		
		USPHealthComponent* HealthComponent = Actor->FindComponentByClass<USPHealthComponent>();
		if(IsValid(HealthComponent) && !HealthComponent->IsDead() && AreEnemies)
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

bool USPAIPerceptionComponent::CheckHostility(AController* Controller1, AController* Controller2) const
{
	if(IsValid(Controller1) && IsValid(Controller2) && Controller1 != Controller2)
	{
		ASPPlayerState* PlayerState1 = Cast<ASPPlayerState>(Controller1->PlayerState);
		ASPPlayerState* PlayerState2 = Cast<ASPPlayerState>(Controller2->PlayerState);
		return IsValid(PlayerState1) && IsValid(PlayerState2) && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}
	return false;
}
