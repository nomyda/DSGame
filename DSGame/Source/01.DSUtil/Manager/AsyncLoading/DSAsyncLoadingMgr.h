#pragma once
#include "Manager/IManager.h"
#include "Pattern/DSSingleton.h"
#include "Engine/StreamableManager.h"

typedef TSharedPtr<FStreamableHandle> SharedStreamableHandle;
DECLARE_DELEGATE_OneParam(FOnLoadingComplete, SharedStreamableHandle);
struct DSAsyncLoadingInfo
{
public:
	SharedStreamableHandle m_HandlePtr;
	TArray<FOnLoadingComplete> m_ArrDelegate_OnLoadingComplete;
};

class DSUTIL_API DSAsyncLoadingM : public IManager, public DSSingleton<DSAsyncLoadingM>
{
public:
	DSAsyncLoadingM();
	~DSAsyncLoadingM();

	bool RequestAsyncLoad(const FString& Path, FOnLoadingComplete rDelegate_OnLoadingComplete);

	void OnInstance();

private:
	void OnLoadingComplete();

	typedef TSortedMap<FString, DSAsyncLoadingInfo> SMap_Path_And_LoadingInfo;
	SMap_Path_And_LoadingInfo m_smapPath_And_AsyncLoadingInfo;
};