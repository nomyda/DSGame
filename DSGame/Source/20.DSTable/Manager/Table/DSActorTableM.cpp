#include "DSActorTableM.h"
#include "Table/Actor/DSActorTable.h"

void DSActorTableM::OnInstance()
{
	AddDataTablePathToLoad(TEXT("DataTable'/Game/Table/Actor/ActorTable.ActorTable'"));
	RequestAsyncLoading();
}