#pragma once
#include "GameFramework/Actor.h"
#include "DSActorInterface.h"
#include "DSActor.generated.h"

/**
 *
 */
UCLASS()
class DSCOREFRAMEWORK_API ADSActor : public AActor, public IDSActorInterface
{
	GENERATED_BODY()

public:
	ADSActor();
	ADSActor(const FObjectInitializer& ObjectInitializer);
	virtual ~ADSActor();

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};