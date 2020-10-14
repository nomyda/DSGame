#pragma once
#include "GameFramework/Pawn.h"
#include "DSActorInterface.h"
#include "DSPawn.generated.h"

/**
 *
 */
UCLASS()
class DSCOREFRAMEWORK_API ADSPawn : public APawn, public IDSActorInterface
{
	GENERATED_BODY()

public:
	ADSPawn();
	ADSPawn(const FObjectInitializer& ObjectInitializer);
	virtual ~ADSPawn();

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};