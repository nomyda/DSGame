// Fill out your copyright notice in the Description page of Project Settings.


#include "DSGameInstance.h"
#include "Manager/IManager.h"
#include "Manager/Table/DSActorTableM.h"



void UDSGameInstance::Init()
{
	Super::Init();
	DSActorTableM::Instance();
	int32 iGot = 0;
}

void UDSGameInstance::Shutdown()
{
	Super::Shutdown();
	//Manager::IManager::ReleaseAll();
}