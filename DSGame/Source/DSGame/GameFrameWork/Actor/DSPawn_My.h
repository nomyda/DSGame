#pragma once
#include "GameFrameWork/Actor/DSPawn.h"
#include "DSPawn_My.generated.h"

/**
 *
 */
UCLASS()
class DS_API ADSPawn_My : public ADSPawn
{
	GENERATED_BODY()
public:
	ADSPawn_My();
	ADSPawn_My(const FObjectInitializer& ObjectInitializer);
	virtual ~ADSPawn_My();

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};