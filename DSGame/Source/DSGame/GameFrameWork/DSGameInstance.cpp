// Fill out your copyright notice in the Description page of Project Settings.


#include "DSGameInstance.h"
#include "Manager/ClientVariable/DSClientVariableM.h"

void UDSGameInstance::Init()
{
	Super::Init();
	Manager::IManager::InitAll();
}

void UDSGameInstance::Shutdown()
{
	Super::Shutdown();
	Manager::IManager::ReleaseAll();
}