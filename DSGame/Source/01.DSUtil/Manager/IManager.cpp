#include "IManager.h"
#include "Misc/AssertionMacros.h"

namespace Manager
{
	TArray<IManager*> IManager::ms_ArrDetailM;

	int32 IManager::InitAll()
	{
		int32 InitCount = 0;
		for (IManager* CurM : ms_ArrDetailM)
		{
			if (nullptr == CurM)
				continue;

			InitCount += CurM->Init();
		}

		return InitCount;
	}

	int32 IManager::ReleaseAll()
	{
		int32 ReleaseCount = 0;
		for (IManager* CurM : ms_ArrDetailM)
		{
			if (nullptr == CurM)
				continue;

			ReleaseCount = CurM->Release();
		}

		return ReleaseCount;
	}
}