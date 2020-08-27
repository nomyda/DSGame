#pragma once
#include "DSPawn.h"
#include "DSPawn_My.generated.h"

/**
 *
 */
UCLASS()
class DS_API ADSPawn_My : public ADSPawn
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};