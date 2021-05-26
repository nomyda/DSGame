#pragma once
#include "GameFramework/Actor.h"
#include "Contents/Puzzle/Tile/DSPuzzleTile.h"
#include "DSPuzzleActor.generated.h"

UCLASS()
class ADSPuzzleActor : public AActor
{
	GENERATED_BODY()

public:
	ADSPuzzleActor();
	ADSPuzzleActor(const FObjectInitializer& ObjectInitializer);
	~ADSPuzzleActor();
	void Constructor();

	static void PuzzleStart(const TArray<FString>& Args);
	void PuzzleStart();

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaSeconds) override;

private:
	void PuzzlePreparation();
	bool FindNextTile(int32& iOutNextTileIndex, float& fSecToStartMoving) const;
	int32 GetNeighborTile(const EDirectionOfMove eDirection, FDSPuzzleTile& rOutPuzzleTile) const;
	bool IsPossibleToMove(const EDirectionOfMove eDirection, const int32 iNeighborTileIndex, const FDSPuzzleTile& rNeighborTile) const;
	bool IsNeighborTile(const int32 LTileIndex, const int32 RTileIndex) const;
	bool IsValid_TileIndex(const int32 TileIndex) const;
	bool GetXY_By_TileIndex(const int32 TileIndex, int32& iOutX, int32& iOutY) const;
	int32 GetTileIndex_By_XY(const int32 iX, const int32 iY) const;
	void UpdateMove();
	void OnMoveFail();
	bool CheckArrive_FinalDestination();

private:
	UPROPERTY(Category = Info, EditAnywhere) int32 Count_Width;
	UPROPERTY(Category = Info, EditAnywhere) int32 Count_Height;
	UPROPERTY(Category = Info, EditAnywhere) int32 Size_Width;
	UPROPERTY(Category = Info, EditAnywhere) int32 Size_Height;
	UPROPERTY(Category = Info, EditAnywhere) TArray<FDSPuzzleTile> Tiles_In_Puzzle;
	TArray<int32> m_StartPoint;
	TArray<int32> m_EndPoint;
	TArray<int32> m_ClosedTileIndex;
	int32 m_iCurTileIndex;
	int32 m_iNextTileIndex;
	float m_fSecToStartMoving;
};
