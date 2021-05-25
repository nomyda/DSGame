#pragma once
#include "IMgr.h"
#include "Pattern\DSSingleton.h"

/*
* 매니저 템플릿 클래스
*/
template<class MgrClass>
class TMgr : public IMgr, public DSSingleton<MgrClass>
{
public:
	virtual ~TMgr() {}
	typedef MgrClass MgrClassType;

	void OnSingleton() final
	{
		const EMgrIndex Index = GetIndex();
		IMgr::AddMgr(Index, this);
		OnInit();
	}
};