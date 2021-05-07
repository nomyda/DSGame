#pragma once
#include "Manager/IManager.h"
#include "Pattern/DSSingleton.h"
#include "Engine/StreamableManager.h"
#include "Containers/SortedMap.h"

static const uint32 InvalidAsyncLoadingID = 0;
typedef TSharedPtr<FStreamableHandle> SharedStreamableHandle;
DECLARE_DELEGATE_TwoParams(FOnLoadingComplete, const uint32, UObject*);
struct DSAsyncLoadingInfo
{
public:
	SharedStreamableHandle m_HandlePtr;
	TArray<FOnLoadingComplete> m_ArrDelegate_OnLoadingComplete;
};

class DSUTIL_API DSAsyncLoadingM : public DSSingleton<DSAsyncLoadingM>
{
public:
	DSAsyncLoadingM();
	~DSAsyncLoadingM();

	bool IsValid() const;
	uint32 RequestAsyncLoading(const FSoftObjectPath& Path, FOnLoadingComplete rDelegate_OnLoadingComplete);
	bool CancelAsyncLoading(const uint32 AsyncLoadingID);

	void OnInstance();

protected:
	FStreamableManager& GetStreamableM() const;

private:
	void OnLoadingComplete();

	typedef TSortedMap<uint32, DSAsyncLoadingInfo> SMap_AsyncLoadID_And_LoadingInfo;
	SMap_AsyncLoadID_And_LoadingInfo m_smapAsyncLoadID_And_AsyncLoadingInfo;
	uint32 m_AsyncLoadID;
};