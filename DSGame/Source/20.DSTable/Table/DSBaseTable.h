#pragma once
#include "Engine/DataTable.h"
#include "DSBaseTable.generated.h"

USTRUCT()
struct FDSBaseTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	virtual ~FDSBaseTable() {}
};