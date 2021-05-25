#include "DSAsyncLoadingMgr.h"
#include "Engine/AssetManager.h"


DSAsyncLoadingM::DSAsyncLoadingM()
	: m_AsyncLoadID(0)
{

}

DSAsyncLoadingM::~DSAsyncLoadingM()
{

}

EMgrIndex DSAsyncLoadingM::GetIndex() const
{
	return EMgrIndex::AsyncLoading;
}

bool DSAsyncLoadingM::IsValid() const
{
	return UAssetManager::IsValid();
}

uint32 DSAsyncLoadingM::RequestAsyncLoading(const FSoftObjectPath& Path, FOnLoadingComplete rDelegate_OnLoadingComplete)
{
	if (false == IsValid())
		return InvalidAsyncLoadingID;

	SharedStreamableHandle HandlePtr = GetStreamableM().RequestAsyncLoad(Path, FStreamableDelegate::CreateRaw(this, &DSAsyncLoadingM::OnLoadingComplete));
	if (false == HandlePtr.IsValid())
		return InvalidAsyncLoadingID;

	uint32 uiCurAsyncLoadID = (++m_AsyncLoadID);
	DSAsyncLoadingInfo& rInfo = m_smapAsyncLoadID_And_AsyncLoadingInfo.FindOrAdd(uiCurAsyncLoadID);
	rInfo.m_HandlePtr = HandlePtr;
	rInfo.m_ArrDelegate_OnLoadingComplete.Add(rDelegate_OnLoadingComplete);
	return uiCurAsyncLoadID;
}

bool DSAsyncLoadingM::CancelAsyncLoading(const uint32 AsyncLoadingID)
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

void DSAsyncLoadingM::OnLoadingComplete()
{
	SMap_AsyncLoadID_And_LoadingInfo::TIterator Itr = m_smapAsyncLoadID_And_AsyncLoadingInfo.CreateIterator();
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
				CurDelegate.ExecuteIfBound((*Itr).Key, rInfo.m_HandlePtr->GetLoadedAsset());
			}

			Itr.RemoveCurrent();
			continue;
		}

		++Itr;
	}
}

FStreamableManager& DSAsyncLoadingM::GetStreamableM() const
{
	static UAssetManager& rAssetM = UAssetManager::Get();
	static FStreamableManager& rStreamableM = rAssetM.GetStreamableManager();
	return rStreamableM;
}