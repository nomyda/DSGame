#include "ITableMgr.h"


ITableM::ArrayString ITableM::m_ArrayString_Empty;
void ITableM::Load(const FName& Key /*= FName()*/)
{
	m_KeyToLoad = Key;
	TArray<FString>& rArray = GetArrayToLoad(Key);
	for (const FString& Cur : rArray)
	{
		DSAsyncLoadingM::Instance().RequestAsyncLoad(Cur, FOnLoadingComplete::CreateRaw(this, &ITableM::OnLoadingComplete));
	}
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

void ITableM::OnLoadingComplete(SharedStreamableHandle SharedHandlePtr)
{
	m_ArrayLoadedHandlePtr.Add(SharedHandlePtr);
}
//
//TableStruct* ITableM::GetTable(const FName& Tid)
//{
//	//for (const FString& Cur : m_ArrayLoadedDataTable)
//	//{
//
//	//}
//	return nullptr;
//}