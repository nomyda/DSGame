#pragma once

template<class UnrealTableStruct>
UnrealTableStruct* ITableM::GetTable(const FName& Tid)
{
	for (UDataTable* CurDataTable: m_ArrayLoadedDataTable)
	{
		if (nullptr == CurDataTable)
			continue;

		UnrealTableStruct* pTable = CurDataTable->FindRow<UnrealTableStruct>(Tid, TEXT(""), false);
		if (nullptr == pTable)
			continue;

		return pTable;
	}

	if (ImmediateLoading())
		return GetTable<UnrealTableStruct>(Tid);

	return nullptr;
}