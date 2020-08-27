#pragma once

#include "Engine/DataTable.h"
#include "Def/DSDefineTable.h"
#include "DSBaseTable.generated.h"

USTRUCT()
struct FDSBaseTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	ETableType Type() const { return m_TableType; }

private:
	ETableType m_TableType;
};