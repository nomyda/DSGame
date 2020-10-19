#include "DSActorM.h"
#include "GameFrameWork/Actor/DSActorInterface.h"
#include "Info/DSActor_SpawnInfo.h"

namespace Manager
{
	Def::EManager_Index DSActorM::GetIndex() const
	{
		return Def::EManager_Index::Actor;
	}

	IDSActorInterface* DSActorM::Appear(const FDSActor_SpawnInfo& Info)
	{
		return nullptr;
	}

	bool DSActorM::Destroy(const int32 ActorID)
	{
		return false;
	}
}