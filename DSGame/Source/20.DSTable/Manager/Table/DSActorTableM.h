#pragma once
#include "DSBaseTableM.h"
#include "Table/Actor/DSActorTable.h"

namespace Manager
{
	class DSTABLE_API DSActorTableM : public DSBaseTableM<DSActorTableM, ::FDSActorTable>
	{
	public:
		DSActorTableM();
	};
}