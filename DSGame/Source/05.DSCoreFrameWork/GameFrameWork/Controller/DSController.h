#pragma once
#include "GameFramework/PlayerController.h"
#include "DSController.generated.h"

/**
 *
 */
UCLASS()
class DSCOREFRAMEWORK_API ADSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void SetupInputComponent() override;
};