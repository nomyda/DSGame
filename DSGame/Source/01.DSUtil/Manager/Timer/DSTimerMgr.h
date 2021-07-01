#pragma once
#include "Manager/TMgr.h"

class DSUTIL_API DSTimerMgr : public TMgr<DSTimerMgr>
{
public:
	DSTimerMgr();
	~DSTimerMgr();
	EMgrIndex GetIndex() const override;

public:
	static float GetRealTimeSeconds(const int64& iTimeSpan = ETimespan::TicksPerSecond);

protected:
	//void OnInit() override;
	//bool OnTick(float fDeltaSeconds) override;

private:
	static FDateTime ms_StandardTime;
};