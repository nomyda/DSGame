// Copyright Epic Games, Inc. All Rights Reserved.


#include "DSGameMode_Play.h"
#include "GameFrameWork/Actor/DSPawn_My.h"

ADSGameMode_Play::ADSGameMode_Play(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = ADSPawn_My::StaticClass();
}

void ADSGameMode_Play::StartPlay()
{
	Super::StartPlay();
}