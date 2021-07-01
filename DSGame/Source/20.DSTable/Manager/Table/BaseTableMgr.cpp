#include "BaseTableMgr.h"


BaseTableM::ArrayString BaseTableM::m_ArrayString_Empty;
BaseTableM::BaseTableM()
	: m_iCount_ImmediateLoading(0)
{

}

void BaseTableM::RequestAsyncLoading(const FName& Key /*= FName()*/)
{
	m_KeyToLoad = Key;
	TArray<FString>& rArray = GetArrayToLoad(Key);
	for (const FString& Cur : rArray)
	{
		uint32 uiAsyncLoadingID = DSAsyncLoadingMgr::Get().RequestAsyncLoading(Cur, FOnLoadingComplete::CreateRaw(this, &BaseTableM::OnAsyncLoadingComplete));
		m_smAsyncLoadingID_AssetPath.Add(uiAsyncLoadingID, Cur);
	}
}

bool BaseTableM::IsLoadingComplete() const
{
	return 0 == m_smAsyncLoadingID_AssetPath.Num();
}

bool BaseTableM::ImmediateLoading()
{
	if (m_smAsyncLoadingID_AssetPath.Num() == 0 || m_iCount_ImmediateLoading >= 1)
		return false;

	++m_iCount_ImmediateLoading;
	for (auto& CurPair : m_smAsyncLoadingID_AssetPath)
	{
		DSAsyncLoadingMgr::Get().CancelAsyncLoading(CurPair.Key);
		UDataTable* pDataTable = LoadObject<UDataTable>(nullptr, *CurPair.Value);
		OnAddDataTable(pDataTable);
	}

	m_smAsyncLoadingID_AssetPath.Empty();
	--m_iCount_ImmediateLoading;
	return true;
}

void BaseTableM::AddDataTablePathToLoad(const FString& DataTablePath, const FName& Key /*= FName()*/)
{
	ArrayString& rArray = m_Key_And_ArrayToLoad.FindOrAdd(Key);
	rArray.Add(DataTablePath);
}

TArray<FString>& BaseTableM::GetArrayToLoad(const FName& Key /*= FName()*/)
{
	ArrayString* pArray = m_Key_And_ArrayToLoad.Find(Key);
	if (nullptr == pArray)
	{
		return m_ArrayString_Empty;
	}

	return *pArray;
}

void BaseTableM::OnAsyncLoadingComplete(const uint32 AsyncLoadID, UObject* pLoadedAsset)
{
	if (nullptr == pLoadedAsset)
		return;

	if (false == m_smAsyncLoadingID_AssetPath.Contains(AsyncLoadID))
		return;

	m_smAsyncLoadingID_AssetPath.Remove(AsyncLoadID);
	UDataTable* pDataTable = Cast<UDataTable>(pLoadedAsset);
	OnAddDataTable(pDataTable);
}

void BaseTableM::OnAddDataTable(UDataTable* pDataTable)
{
	if (nullptr == pDataTable)
		return;

	if (m_ArrayLoadedDataTable.Contains(pDataTable))
		return;

	m_ArrayLoadedDataTable.Add(pDataTable);
	if (pDataTable->IsRooted())
		return;

	pDataTable->AddToRoot();
}