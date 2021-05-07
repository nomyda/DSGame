#include "ITableMgr.h"


ITableM::ArrayString ITableM::m_ArrayString_Empty;
void ITableM::RequestAsyncLoading(const FName& Key /*= FName()*/)
{
	m_KeyToLoad = Key;
	TArray<FString>& rArray = GetArrayToLoad(Key);
	for (const FString& Cur : rArray)
	{
		uint32 uiAsyncLoadingID = DSAsyncLoadingM::Instance().RequestAsyncLoading(Cur, FOnLoadingComplete::CreateRaw(this, &ITableM::OnAsyncLoadingComplete));
		m_smAsyncLoadingID_AssetPath.Add(uiAsyncLoadingID, Cur);
	}
}

bool ITableM::ImmediateLoading()
{
	if (m_smAsyncLoadingID_AssetPath.Num() == 0)
		return false;

	for (auto& CurPair : m_smAsyncLoadingID_AssetPath)
	{
		DSAsyncLoadingM::Instance().CancelAsyncLoading(CurPair.Key);
		UDataTable* pDataTable = LoadObject<UDataTable>(nullptr, *CurPair.Value);
		OnAddDataTable(pDataTable);
	}

	m_smAsyncLoadingID_AssetPath.Empty();
	return true;
}

void ITableM::AddDataTablePathToLoad(const FString& DataTablePath, const FName& Key /*= FName()*/)
{
	ArrayString& rArray = m_Key_And_ArrayToLoad.FindOrAdd(Key);
	rArray.Add(DataTablePath);
}

TArray<FString>& ITableM::GetArrayToLoad(const FName& Key /*= FName()*/)
{
	ArrayString* pArray = m_Key_And_ArrayToLoad.Find(Key);
	if (nullptr == pArray)
	{
		return m_ArrayString_Empty;
	}

	return *pArray;
}

void ITableM::OnAsyncLoadingComplete(const uint32 AsyncLoadID, UObject* pLoadedAsset)
{
	if (nullptr == pLoadedAsset)
		return;

	if (false == m_smAsyncLoadingID_AssetPath.Contains(AsyncLoadID))
		return;

	m_smAsyncLoadingID_AssetPath.Remove(AsyncLoadID);
	UDataTable* pDataTable = Cast<UDataTable>(pLoadedAsset);
	OnAddDataTable(pDataTable);
}

void ITableM::OnAddDataTable(UDataTable* pDataTable)
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