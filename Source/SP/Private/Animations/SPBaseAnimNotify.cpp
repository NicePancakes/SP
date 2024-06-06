#include "Animations/SPBaseAnimNotify.h"

void USPBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	OnNotifiedSignature.Broadcast(MeshComp);
}
