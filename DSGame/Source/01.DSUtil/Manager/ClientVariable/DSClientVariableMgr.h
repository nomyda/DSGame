#pragma once
#include "Manager/TMgr.h"

class DSUTIL_API DSClientVariableMgr : public TMgr<DSClientVariableMgr>
{
public:
	EMgrIndex GetIndex() const override;
	void RegistConsolCommand(const TCHAR* FuncKey, const FConsoleCommandWithArgsDelegate& CommandDelegate, const FString& Help);
	void UnRegistConsolCommand(const TCHAR* FuncKey);

protected:
	//void OnInit() override;

private:
	TSortedMap<FString, IConsoleCommand*> m_smapName_And_ConsoleCommand;
};

#define DS_Regist_Console_Command( Command, FuncName, Help ) \
	DSClientVariableMgr::Get().RegistConsolCommand( Command, FConsoleCommandWithArgsDelegate::CreateStatic( FuncName ), Help );