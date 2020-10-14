#include "DSActor.h"

ADSActor::ADSActor()
	: Super()
{
}

ADSActor::ADSActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ADSActor::~ADSActor()
{

}

void ADSActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADSActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}