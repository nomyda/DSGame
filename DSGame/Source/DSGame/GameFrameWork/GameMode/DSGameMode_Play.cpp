// Copyright Epic Games, Inc. All Rights Reserved.


#include "DSGameMode_Play.h"
#include "GameFrameWork/Actor/DSPawn_My.h"
#include "GameFrameWork/Controller/DSController_Play.h"

ADSGameMode_Play::ADSGameMode_Play(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = ADSPawn_My::StaticClass();
	PlayerControllerClass = ADSPlayerController_Play::StaticClass();
}

void ADSGameMode_Play::StartPlay()
{
	Super::StartPlay();
}