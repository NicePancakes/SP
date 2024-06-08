#include "AI/SPAIBaseCharacter.h"
#include "AI/SPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SPAIWeaponComponent.h"
#include "BrainComponent.h"

ASPAIBaseCharacter::ASPAIBaseCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USPAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASPAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ASPAIBaseCharacter::OnDeath()
{
	Super::OnDeath();

	AAIController* AIController = Cast<AAIController>(Controller);
	if(IsValid(AIController) && IsValid(AIController->BrainComponent))
	{
		AIController->BrainComponent->Cleanup();
	}
}
