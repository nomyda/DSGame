#pragma once
#include "Manager/IManager.h"
#include "Engine/DataTable.h"
#include "Manager/AsyncLoading/DSAsyncLoadingMgr.h"

class DSTABLE_API ITableM : public IManager
{
public:
	virtual ~ITableM() {}
	void RequestAsyncLoading(const FName& Key = FName());

	template<class UnrealTableStruct>
	UnrealTableStruct* GetTable(const FName& Tid);

protected:
	typedef TArray<FString> ArrayString;
	bool ImmediateLoading();
	void AddDataTablePathToLoad(const FString& DataTablePath, const FName& Key = FName());
	ArrayString& GetArrayToLoad(const FName& Key = FName());
	virtual void OnAsyncLoadingComplete(const uint32 AsyncLoadID, UObject* pLoadedAsset);
	virtual void OnAddDataTable(UDataTable* pDataTable);

protected:
	TSortedMap<FName, ArrayString, FDefaultAllocator, FNameFastLess> m_Key_And_ArrayToLoad;
	TSortedMap<uint32, FString> m_smAsyncLoadingID_AssetPath;
	TArray<UDataTable*> m_ArrayLoadedDataTable;
	FName m_KeyToLoad;

	static ArrayString m_ArrayString_Empty;
};


#include "ITableMgr.hpp"