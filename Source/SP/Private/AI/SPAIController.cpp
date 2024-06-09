#include "AI/SPAIController.h"
#include "AI/SPAIBaseCharacter.h"
#include "Components/SPAIPerceptionComponent.h"
#include "Components/SPRespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASPAIController::ASPAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<USPAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>(TEXT("RespawnComponent"));

	bWantsPlayerState = true;
}

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASPAIBaseCharacter* AICharacter = Cast<ASPAIBaseCharacter>(InPawn);
	if(IsValid(AICharacter))
	{
		RunBehaviorTree(AICharacter->GetBehaviorTree());
	}
}

void ASPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AActor* AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ASPAIController::GetFocusOnActor() const
{
	if(IsValid(GetBlackboardComponent()))
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}
	return nullptr;
}
