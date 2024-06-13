#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SPGameInstance.generated.h"


UCLASS()
class SP_API USPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetPlayerCounts(int32 PlayerCounts) { PlayersNum = PlayerCounts; };
	int32 GetPlayerNum() const {return PlayersNum; }

	void SetIsLeftHandMode(bool bIsLeftMode) { bIsLeftHandMode = bIsLeftMode; };
	bool GetIsLeftHandMode() const { return bIsLeftHandMode; }

private:
	int32 PlayersNum = 0;
	bool bIsLeftHandMode = false;
};
