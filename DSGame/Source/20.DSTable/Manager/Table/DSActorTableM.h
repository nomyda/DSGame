#pragma once
#include "ITableMgr.h"
#include "Table/Actor/DSActorTable.h"

class DSTABLE_API DSActorTableM : public ITableM, public DSSingleton<DSActorTableM>
{
public:
	void OnInstance();
};