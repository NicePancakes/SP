#pragma once

#include "CoreMinimal.h"
#include "Player/SPBaseCharacter.h"
#include "SPAIBaseCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SP_API ASPAIBaseCharacter : public ASPBaseCharacter
{
	GENERATED_BODY()

public:
	ASPAIBaseCharacter(const FObjectInitializer& ObjectInitializer);
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; };

protected:
	virtual void OnDeath() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};
