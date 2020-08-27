// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameModeBase.h"
#include "DSGameMode.generated.h"


class UDSUserWidget;

/**
 * 
 */
UCLASS()
class DS_API ADSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADSGameMode(const FObjectInitializer& ObjectInitializer);
	void StartPlay() override;

public:
	UDSUserWidget* GetUserWidget() { return m_UserWidget; }

private:
	UPROPERTY() UDSUserWidget* m_UserWidget;
};
