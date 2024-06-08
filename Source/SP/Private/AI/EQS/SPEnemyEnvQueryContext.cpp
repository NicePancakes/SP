#include "AI/EQS/SPEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USPEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	UBlackboardComponent* BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if(IsValid(BlackboardComponent))
	{
		AActor* ContextActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKeyName));
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
	}

}
