#include "IMgr.h"
#include "Containers/Ticker.h"

TSortedMap<EMgrIndex, IMgr*> IMgr::ms_smapMgr;
FDelegateHandle IMgr::ms_dgTickHandle;

void IMgr::AddMgr(const EMgrIndex Index, IMgr* pMgr)
{
	if (ms_smapMgr.Contains(Index) || nullptr == pMgr)
		return;

	ms_smapMgr.Add(Index, pMgr);	
}

void IMgr::InitMgr()
{
	ms_dgTickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateStatic(&IMgr::TickMgr));
}

void IMgr::ShutdownMgr()
{
	FTicker::GetCoreTicker().RemoveTicker(ms_dgTickHandle);
	for (auto& CurPair : ms_smapMgr)
	{
		if (nullptr == CurPair.Value)
			continue;

		CurPair.Value->OnShutdown();
	}
	ms_smapMgr.Empty();
}

bool IMgr::TickMgr(float fDeltaSeconds)
{
	for (auto& CurPair : ms_smapMgr)
	{
		if (nullptr == CurPair.Value)
			continue;

		CurPair.Value->OnTick(fDeltaSeconds);
	}

	return true;
}