#pragma once
#include "DSController.h"
#include "DSController_Play.generated.h"

/**
 *
 */
UCLASS()
class DS_API ADSPlayerController_Play : public ADSPlayerController
{
	GENERATED_BODY()
public:
	

protected:
	void SetupInputComponent() override;

private:
	void OnMousePressed();
	void OnMouseRelease();
	//void OnMouseMoveX(float fDelta);
	//void OnMouseMoveY(float fDelta);
	void PlayerTick(float DeltaTime) override;
};