#pragma once

#include "Engine/DataTable.h"
#include "Def/DSDefineTable.h"
#include "DSBaseTable.generated.h"

USTRUCT()
struct FDSBaseTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FDSBaseTable()
	{

	}

	virtual ETableType Type() const { return ETableType::None; }
};