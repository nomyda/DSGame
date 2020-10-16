#pragma once
#include "Manager/Def/DSManagerDefine.h"

namespace Manager
{
	class DSUTIL_API IManager
	{
	public:		
		virtual Def::EManager_Index GetIndex() const { return Def::EManager_Index::None; }
		static int32 InitAll();
		static int32 ReleaseAll();

	protected:
		virtual bool Init() { return false; };
		virtual bool Release() { return false; };

	protected:
		static IManager* ms_DetailM[static_cast<int32>(Def::EManager_Index::Max)];
	};
}