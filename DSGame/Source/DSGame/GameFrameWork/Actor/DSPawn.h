#pragma once
#include "GameFramework/Pawn.h"
#include "DSActorInterface.h"
#include "DSPawn.generated.h"

/**
 *
 */
UCLASS()
class DS_API ADSPawn : public APawn, public IDSActorInterface
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};