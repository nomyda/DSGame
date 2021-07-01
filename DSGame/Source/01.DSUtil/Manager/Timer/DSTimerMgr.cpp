#include "DSTimerMgr.h"

FDateTime DSTimerMgr::ms_StandardTime = FDateTime();

DSTimerMgr::DSTimerMgr()
{
	ms_StandardTime = FDateTime::UtcNow();
}

DSTimerMgr::~DSTimerMgr()
{
}

EMgrIndex DSTimerMgr::GetIndex() const
{
	return EMgrIndex::Timer;
}

//void DSTimerMgr::OnInit()
//{
//}
//
//bool DSTimerMgr::OnTick(float fDeltaSeconds)
//{
//	return true;
//}

float DSTimerMgr::GetRealTimeSeconds(const int64& iTimeSpan /*= ETimespan::TicksPerSecond*/)
{
	return (FDateTime::UtcNow().GetTicks() - ms_StandardTime.GetTicks()) / static_cast<float>(iTimeSpan);
}