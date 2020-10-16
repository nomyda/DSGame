#include "IManager.h"

namespace Manager
{
	IManager* IManager::ms_DetailM[] = {nullptr,};

	int32 IManager::InitAll()
	{
		int32 InitCount = 0;
		for (int32 Index = 0; Index < static_cast<int32>(Def::EManager_Index::Max); ++Index)
		{
			IManager* CurM = ms_DetailM[Index];
			if (nullptr == CurM)
				continue;

			InitCount += CurM->Init();
		}

		return InitCount;
	}

	int32 IManager::ReleaseAll()
	{
		int32 ReleaseCount = 0;
		for (int32 Index = 0; Index < static_cast<int32>(Def::EManager_Index::Max); ++Index)
		{
			IManager* CurM = ms_DetailM[Index];
			if (nullptr == CurM)
				continue;

			ReleaseCount = CurM->Release();
		}

		return ReleaseCount;
	}
}