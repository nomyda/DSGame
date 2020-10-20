#include "DSActorTableM.h"

namespace Manager
{
	DSActorTableM::DSActorTableM()
		: DSBaseTableM<DSActorTableM, ::FDSActorTable>()
	{
		AddAssetPath(TEXT("DataTable'/Game/Table/Actor/ActorTable.ActorTable'"));
	}
}