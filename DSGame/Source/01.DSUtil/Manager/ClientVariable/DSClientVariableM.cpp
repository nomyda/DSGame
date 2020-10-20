#include "DSClientVariableM.h"

namespace Manager
{
	void DSClientVariableM::RegistConsolCommand(const TCHAR* FuncKey, const FConsoleCommandWithArgsDelegate& CommandDelegate, const FString& Help)
	{
		IConsoleManager::Get().RegisterConsoleCommand(FuncKey, *Help, CommandDelegate, ECVF_SetByCommandline);
	}
}