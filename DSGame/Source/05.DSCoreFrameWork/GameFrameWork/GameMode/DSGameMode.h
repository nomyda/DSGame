// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameModeBase.h"
#include "DSGameMode.generated.h"


/**
 * 
 */
UCLASS()
class DSCOREFRAMEWORK_API ADSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADSGameMode(const FObjectInitializer& ObjectInitializer);
	void StartPlay() override;
};
