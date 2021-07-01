// Fill out your copyright notice in the Description page of Project Settings.


#include "DSGameInstance.h"
#include "Manager/Ue4/DSUe4Mgr.h"
#include "Manager/IMgr.h"


void UDSGameInstance::Init()
{
	Super::Init();
	DSUe4Mgr::Get().SetGameInstance(this);
	IMgr::InitMgr();
}

void UDSGameInstance::Shutdown()
{
	Super::Shutdown();
	IMgr::ShutdownMgr();
	DSUe4Mgr::Get().SetGameInstance(nullptr);
}