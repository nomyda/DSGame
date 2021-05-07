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

	UPROPERTY(EditAnywhere) TSoftObjectPtr<UStreamableRenderAsset> ModelMesh;
	UPROPERTY(EditAnywhere) TSoftObjectPtr<UAnimBlueprint> AnimBP;
};