#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPAIController.generated.h"

class USPAIPerceptionComponent;
class USPRespawnComponent;

UCLASS()
class SP_API ASPAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASPAIController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	AActor* GetFocusOnActor() const; 

protected:
	UPROPERTY(EditDefaultsOnly, Category  = "Components")
	TObjectPtr<USPAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, Category  = "Components")
	TObjectPtr<USPRespawnComponent> RespawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
};
