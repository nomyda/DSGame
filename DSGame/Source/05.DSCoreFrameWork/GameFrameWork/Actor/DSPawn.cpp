#include "DSPawn.h"

ADSPawn::ADSPawn()
	: Super()
{

}

ADSPawn::ADSPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

ADSPawn::~ADSPawn()
{

}

void ADSPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADSPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}