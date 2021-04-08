#pragma once

template<class UnrealTableStruct>
UnrealTableStruct* ITableM::GetTable(const FName& Tid)
{
	for (SharedStreamableHandle& CurHandle: m_ArrayLoadedHandlePtr)
	{
		if (false == CurHandle.IsValid())
			continue;

		if (false == CurHandle->HasLoadCompleted())
			continue;

		UObject* pLoadedAsset = CurHandle->GetLoadedAsset();
		if (nullptr == pLoadedAsset)
			continue;

		UDataTable* pLoadedDataTable = Cast<UDataTable>(pLoadedAsset);
		if (nullptr == pLoadedDataTable)
			continue;

		UnrealTableStruct* pTable = pLoadedDataTable->FindRow<UnrealTableStruct>(Tid, TEXT(""), false);
		if (nullptr == pTable)
			continue;

		return pTable;
	}

	return nullptr;
}