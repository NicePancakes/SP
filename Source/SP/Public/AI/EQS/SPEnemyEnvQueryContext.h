#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SPEnemyEnvQueryContext.generated.h"


UCLASS()
class SP_API USPEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

protected:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";
};
