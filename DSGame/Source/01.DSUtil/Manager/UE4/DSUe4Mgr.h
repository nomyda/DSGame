#pragma once
#include "Manager/TMgr.h"

class DSUTIL_API DSUe4Mgr : public TMgr<DSUe4Mgr>
{
public:
	DSUe4Mgr();
	~DSUe4Mgr();
	EMgrIndex GetIndex() const override;

	void SetGameInstance(UGameInstance* pGameInstance);
	UGameInstance* GetGameInstance();
	UWorld* GetWorld();
	APlayerController* GetCurrentPlayerController();

private:
	typedef TWeakObjectPtr<UGameInstance> WeakGameInstancePtr;
	WeakGameInstancePtr m_wpGameInstance;
};