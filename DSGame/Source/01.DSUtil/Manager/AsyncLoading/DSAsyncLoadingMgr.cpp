#include "DSAsyncLoadingMgr.h"
#include "Engine/AssetManager.h"


DSAsyncLoadingMgr::DSAsyncLoadingMgr()
	: m_AsyncLoadID(0)
{

}

DSAsyncLoadingMgr::~DSAsyncLoadingMgr()
{

}

EMgrIndex DSAsyncLoadingMgr::GetIndex() const
{
	return EMgrIndex::AsyncLoading;
}

bool DSAsyncLoadingMgr::IsValid() const
{
	return UAssetManager::IsValid();
}

uint32 DSAsyncLoadingMgr::RequestAsyncLoading(const FSoftObjectPath& Path, FOnLoadingComplete rDelegate_OnLoadingComplete)
{
	if (false == IsValid())
		return InvalidAsyncLoadingID;

	SharedStreamableHandle HandlePtr = GetStreamableM().RequestAsyncLoad(Path, FStreamableDelegate::CreateRaw(this, &DSAsyncLoadingMgr::OnLoadingComplete));
	if (false == HandlePtr.IsValid())
		return InvalidAsyncLoadingID;

	uint32 uiCurAsyncLoadID = (++m_AsyncLoadID);
	DSAsyncLoadingInfo& rInfo = m_smapAsyncLoadID_And_AsyncLoadingInfo.FindOrAdd(uiCurAsyncLoadID);
	rInfo.m_HandlePtr = HandlePtr;
	rInfo.m_ArrDelegate_OnLoadingComplete.Add(rDelegate_OnLoadingComplete);
	return uiCurAsyncLoadID;
}

bool DSAsyncLoadingMgr::CancelAsyncLoading(const uint32 AsyncLoadingID)
{
	if (false == IsValid())
		return false;

	DSAsyncLoadingInfo* pInfo = m_smapAsyncLoadID_And_AsyncLoadingInfo.Find(AsyncLoadingID);
	if (nullptr == pInfo)
		return false;

	if (false == pInfo->m_HandlePtr.IsValid())
		return false;

	pInfo->m_HandlePtr->CancelHandle();
	m_smapAsyncLoadID_And_AsyncLoadingInfo.Remove(AsyncLoadingID);
	return true;
}

void DSAsyncLoadingMgr::OnLoadingComplete()
{
	SMap_AsyncLoadID_And_LoadingInfo::TIterator Itr = m_smapAsyncLoadID_And_AsyncLoadingInfo.CreateIterator();
	while (Itr)
	{
		DSAsyncLoadingInfo& rInfo = (*Itr).Value;
		if (false == rInfo.m_HandlePtr.IsValid())
		{
			Itr.RemoveCurrent();
			++Itr;
			continue;
		}

		if (rInfo.m_HandlePtr->HasLoadCompleted())
		{
			for (auto& CurDelegate : rInfo.m_ArrDelegate_OnLoadingComplete)
			{
				CurDelegate.ExecuteIfBound((*Itr).Key, rInfo.m_HandlePtr->GetLoadedAsset());
			}

			Itr.RemoveCurrent();
		}

		++Itr;
	}
}

FStreamableManager& DSAsyncLoadingMgr::GetStreamableM() const
{
	static UAssetManager& rAssetM = UAssetManager::Get();
	static FStreamableManager& rStreamableM = rAssetM.GetStreamableManager();
	return rStreamableM;
}