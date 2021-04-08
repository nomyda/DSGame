#pragma once
#include "Manager/IManager.h"
#include "Engine/DataTable.h"
#include "Manager/AsyncLoading/DSAsyncLoadingMgr.h"

class ITableM : public IManager
{
public:
	virtual ~ITableM() {}
	void Load(const FName& Key = FName());

	template<class UnrealTableStruct>
	UnrealTableStruct* GetTable(const FName& Tid);

protected:
	typedef TArray<FString> ArrayString;
	void AddDataTablePathToLoad(const FString& DataTablePath, const FName& Key = FName());
	ArrayString& GetArrayToLoad(const FName& Key = FName());
	virtual void OnLoadingComplete(SharedStreamableHandle SharedHandlePtr);

protected:
	TSortedMap<FName, ArrayString, FDefaultAllocator, FNameFastLess> m_Key_And_ArrayToLoad;
	TArray<SharedStreamableHandle> m_ArrayLoadedHandlePtr;
	FName m_KeyToLoad;

	static ArrayString m_ArrayString_Empty;
};


#include "ITableMgr.hpp"