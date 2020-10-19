#pragma once
#include "CoreMinimal.h"

struct FDSActor_SpawnInfo
{
public:
	int32 m_ActorID;
	FName m_ActorTableTid;
	FVector m_vPos;
	float m_fAngle;
};