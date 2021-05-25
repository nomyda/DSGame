#pragma once
#include "Containers/SortedMap.h"

enum class EMgrIndex : int16
{
	ClientVariable,
	Timer,
	AsyncLoading,
	Max,
};

class DSCORE_API IMgr
{
public:
	virtual ~IMgr() {}
	virtual EMgrIndex GetIndex() const = 0;

public:
	static void AddMgr(const EMgrIndex Index, IMgr* pMgr);
	static void InitMgr();
	static void ShutdownMgr();

protected:
	static bool TickMgr(float fDeltaSeconds);
	virtual void OnInit() {}
	virtual void OnShutdown() {}
	virtual bool OnTick(float fDeltaSeconds) { return false; }

private:
	static TSortedMap<EMgrIndex, IMgr*> ms_smapMgr;
	static FDelegateHandle ms_dgTickHandle;
};