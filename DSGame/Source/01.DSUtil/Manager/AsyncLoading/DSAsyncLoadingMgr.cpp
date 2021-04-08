#include "DSAsyncLoadingMgr.h"
#include "Engine/AssetManager.h"



DSAsyncLoadingM::DSAsyncLoadingM()
{

}

DSAsyncLoadingM::~DSAsyncLoadingM()
{

}

bool DSAsyncLoadingM::RequestAsyncLoad(const FString& Path, FOnLoadingComplete rDelegate_OnLoadingComplete)
{
	UAssetManager& rAssetM = UAssetManager::Get();
	FStreamableManager& rStreamableM = rAssetM.GetStreamableManager();


	FSoftObjectPath RequestAssetPath(Path);	
	SharedStreamableHandle HandlePtr = rStreamableM.RequestAsyncLoad(RequestAssetPath, FStreamableDelegate::CreateRaw(this, &DSAsyncLoadingM::OnLoadingComplete));
	if (false == HandlePtr.IsValid())
		return false;

	DSAsyncLoadingInfo& rInfo = m_smapPath_And_AsyncLoadingInfo.FindOrAdd(Path);
	rInfo.m_HandlePtr = HandlePtr;
	rInfo.m_ArrDelegate_OnLoadingComplete.Add(rDelegate_OnLoadingComplete);
	return true;
}

void DSAsyncLoadingM::OnInstance()
{

}

void DSAsyncLoadingM::OnLoadingComplete()
{
	SMap_Path_And_LoadingInfo::TIterator Itr = m_smapPath_And_AsyncLoadingInfo.CreateIterator();
	while (Itr)
	{
		DSAsyncLoadingInfo& rInfo = (*Itr).Value;
		if (false == rInfo.m_HandlePtr.IsValid())
		{
			Itr.RemoveCurrent();
			continue;
		}

		if (rInfo.m_HandlePtr->HasLoadCompleted())
		{
			for (auto& CurDelegate : rInfo.m_ArrDelegate_OnLoadingComplete)
			{
				CurDelegate.ExecuteIfBound(rInfo.m_HandlePtr);
			}

			Itr.RemoveCurrent();
			continue;
		}

		++Itr;
	}
}