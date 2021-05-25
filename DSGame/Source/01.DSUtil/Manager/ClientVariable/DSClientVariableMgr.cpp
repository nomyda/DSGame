#include "DSClientVariableMgr.h"


EMgrIndex DSClientVariableMgr::GetIndex() const
{
	return EMgrIndex::ClientVariable;
}

void DSClientVariableMgr::RegistConsolCommand(const TCHAR* FuncKey, const FConsoleCommandWithArgsDelegate& CommandDelegate, const FString& Help)
{
	if (m_smapName_And_ConsoleCommand.Contains(FuncKey))
		return;

	IConsoleCommand* pConsoleCommand = IConsoleManager::Get().RegisterConsoleCommand(FuncKey, *Help, CommandDelegate, ECVF_SetByCommandline);
	if (nullptr == pConsoleCommand)
		return;

	m_smapName_And_ConsoleCommand.Add(FuncKey, pConsoleCommand);
}

void DSClientVariableMgr::UnRegistConsolCommand(const TCHAR* FuncKey)
{
	if (false == m_smapName_And_ConsoleCommand.Contains(FuncKey))
		return;

	m_smapName_And_ConsoleCommand.Remove(FuncKey);
}

//void DSClientVariableMgr::OnInit()
//{
//
//}