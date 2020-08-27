// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "DSGameMode.h"
#include "DSGameMode_Play.generated.h"

/**
 * 
 */
UCLASS()
class DS_API ADSGameMode_Play : public ADSGameMode
{
	GENERATED_BODY()

public:
	ADSGameMode_Play(const FObjectInitializer& ObjectInitializer);
	void StartPlay() override;
};
