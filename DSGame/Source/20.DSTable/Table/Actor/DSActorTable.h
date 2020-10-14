#pragma once
#include "Table/DSBaseTable.h"
#include "DSActorTable.generated.h"

USTRUCT()
struct FDSActorTable : public FDSBaseTable
{
	GENERATED_BODY()

public:
	FDSActorTable()
		: Super()
	{

	}

	ETableType Type() const override { return ETableType::Actor; }
	UPROPERTY(EditAnywhere) int32 Take2;
};