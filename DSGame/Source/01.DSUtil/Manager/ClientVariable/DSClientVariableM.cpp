#include "DSClientVariableM.h"

namespace Manager
{
	Def::EManager_Index DSClientVariableM::GetIndex() const
	{
		return Def::EManager_Index::ClientVariable;
	}

	void DSClientVariableM::RegistConsolCommand(const TCHAR* FuncKey, const FConsoleCommandWithArgsDelegate& CommandDelegate, const FString& Help)
	{
		IConsoleManager::Get().RegisterConsoleCommand(FuncKey, *Help, CommandDelegate, ECVF_SetByCommandline);
	}
}