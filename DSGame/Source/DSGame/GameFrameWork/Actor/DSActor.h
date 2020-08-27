#pragma once
#include "GameFramework/Actor.h"
#include "DSActorInterface.h"
#include "DSActor.generated.h"

/**
 *
 */
UCLASS()
class DS_API ADSActor : public AActor, public IDSActorInterface
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};