#pragma once
#include "Manager/Def/DSManagerDefine.h"

namespace Manager
{
	class DSUTIL_API IManager
	{
	public:		
		static int32 InitAll();
		static int32 ReleaseAll();

	protected:
		virtual bool Init() { return false; };
		virtual bool Release() { return false; };

	protected:
		static TArray<IManager*> ms_ArrDetailM;
	};
}