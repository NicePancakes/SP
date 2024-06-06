#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SPBaseAnimNotify.generated.h"


UCLASS()
class SP_API USPBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifiedSignature& GetOnNotifiedSignature() { return OnNotifiedSignature; }

private:
	FOnNotifiedSignature OnNotifiedSignature;
};
