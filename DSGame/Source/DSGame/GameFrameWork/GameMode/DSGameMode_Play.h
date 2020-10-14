// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFrameWork/GameMode/DSGameMode.h"
#include "DSGameMode_Play.generated.h"


class UDSUserWidget;

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

public:
	UDSUserWidget* GetUserWidget() { return m_UserWidget; }

private:
	UPROPERTY() UDSUserWidget* m_UserWidget;
};
