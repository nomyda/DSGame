#pragma once

template<class UnrealTableStruct>
UnrealTableStruct* BaseTableM::GetTable(const FName& Tid, const bool bLoad /*= false*/)
{
	if (bLoad)
		ImmediateLoading();

	for (UDataTable* CurDataTable: m_ArrayLoadedDataTable)
	{
		if (nullptr == CurDataTable)
			continue;

		UnrealTableStruct* pTable = CurDataTable->FindRow<UnrealTableStruct>(Tid, TEXT(""), false);
		if (nullptr == pTable)
			continue;

		return pTable;
	}

	return nullptr;
}

template<class UnrealTableStruct>
void BaseTableM::GetTable(const FName& Tid, TFunction<void(UnrealTableStruct*)> Callback)
{
	UnrealTableStruct* pTable = GetTable<UnrealTableStruct>(Tid, false);
	if (nullptr == pTable)
	{
		Callback(pTable);
		return;
	}
}