#pragma once
#include "DSPuzzleTile.generated.h"

UENUM()
enum class ETileType : int16
{
	Fix,
	Rotatable,
	StartPoint,
	EndPoint,
	Max,
};

enum class EDirectionOfMove : int16
{
	TopSide,
	LeftSide,
	RightSide,
	DownSide,
	Max,
};

static const float SecToGoFromTileToTile = 3.0f;	// Ÿ�Ͽ��� Ÿ�ϰ� �̵��ϴµ� �ɸ��� �ð�


USTRUCT()
struct FDSPuzzleTile
{
	GENERATED_BODY()

public:
	FDSPuzzleTile();
	~FDSPuzzleTile();

	UPROPERTY(Category = Info, EditAnywhere) uint32 TileIndex;
	UPROPERTY(Category = Info, EditAnywhere) ETileType TileType;
};

