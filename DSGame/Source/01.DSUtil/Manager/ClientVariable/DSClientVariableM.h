#pragma once
#include "Manager/DSBaseM.h"
#include "HAL/IConsoleManager.h"

namespace Manager
{
	class DSUTIL_API DSClientVariableM : public DSBaseM<DSClientVariableM>
	{
	public:
		Def::EManager_Index GetIndex() const override;
		void RegistConsolCommand(const TCHAR* FuncKey, const FConsoleCommandWithArgsDelegate& CommandDelegate, const FString& Help);

	protected:
		// IManager
		bool Init() override { return false; };
		bool Release() override { return false; };
	};
}

#define DS_Regist_Console_Command( Command, FuncName, Help ) \
	Manager::GetM().RegistConsolCommand( Command, FConsoleCommandWithArgsDelegate::CreateStatic( FuncName ), Help );