#include "DSController_Play.h"




void ADSPlayerController_Play::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (nullptr == InputComponent)
		return;

	InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Pressed, this, &ADSPlayerController_Play::OnMousePressed);
	InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Released, this, &ADSPlayerController_Play::OnMouseRelease);
	//InputComponent->BindAxis(TEXT("MouseMoveX"), this, &ADSPlayerController_Play::OnMouseMoveX);
	//InputComponent->BindAxis(TEXT("MouseMoveY"), this, &ADSPlayerController_Play::OnMouseMoveY);
}

void ADSPlayerController_Play::OnMousePressed()
{

}

void ADSPlayerController_Play::OnMouseRelease()
{

}

//void ADSPlayerController_Play::OnMouseMoveX(float fDelta)
//{
//}
//
//void ADSPlayerController_Play::OnMouseMoveY(float fDelta)
//{
//}

void ADSPlayerController_Play::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (nullptr == Player)
		return;

	UGameViewportClient* ViewportClient = CastChecked<ULocalPlayer>(Player)->ViewportClient;
	if (nullptr == ViewportClient)
		return;

	FVector2D vMousePos;
	if (false == ViewportClient->GetMousePosition(vMousePos))
		return;

	FVector2D vViewportSize;
	ViewportClient->GetViewportSize(vViewportSize);
	if (vMousePos.X < 10.0f || vMousePos.X >= vViewportSize.X ||
		vMousePos.Y < 10.0f || vMousePos.Y >= vViewportSize.Y)
	{

	}
	//FHitResult HitResult;
	//CurrentClickTraceChannel = DefaultClickTraceChannel;
	//const bool bHit = GetHitResultAtScreenPosition(vMousePos, CurrentClickTraceChannel, true, HitResult);
}