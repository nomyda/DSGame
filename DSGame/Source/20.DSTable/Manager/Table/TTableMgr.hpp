#pragma once

template<class UnrealTableStruct, class TableManagerClass>
UnrealTableStruct* TTableM<UnrealTableStruct, TableManagerClass>::GetTable(const FName& Tid, const bool bLoad /*= false*/)
{
	return BaseTableM::GetTable<UnrealTableStruct>(Tid, bLoad);
}

template<class UnrealTableStruct, class TableManagerClass>
void TTableM<UnrealTableStruct, TableManagerClass>::GetTable(const FName& Tid, TDelegate_GetTable dgGetTable)
{
	if (IsLoadingComplete())
	{
		UnrealTableStruct* pTable = GetTable(Tid);
		dgGetTable.Execute(pTable);
		return;
	}

	m_smTid_And_Delegate.Add(Tid, dgGetTable);
}

template<class UnrealTableStruct, class TableManagerClass>
void TTableM<UnrealTableStruct, TableManagerClass>::OnTick(float fDeltaSeconds)
{
	if (false == IsLoadingComplete())
		return;

	for (auto& Pair : m_smTid_And_Delegate)
	{
		UnrealTableStruct* pTable = GetTable(Pair.Key);
		Pair.Value.ExecuteIfBound(pTable);
	}

	m_smTid_And_Delegate.Empty();
}