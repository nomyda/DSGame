#include "DSPuzzleActor.h"
#include "Manager/ClientVariable/DSClientVariableMgr.h"
#include "Manager/Timer/DSTimerMgr.h"


/*
* 퍼즐 흐름도
* 1. 이동할 방향을 선택
* 2. 목표 타일을 향해 이동
*/
static const TCHAR* ConsolCommandName_PuzzleStart = TEXT("Ds.Puzzle.Start");
ADSPuzzleActor::ADSPuzzleActor()
	: AActor()
{
	Constructor();
}

ADSPuzzleActor::ADSPuzzleActor(const FObjectInitializer& ObjectInitializer)
	: AActor(ObjectInitializer)
{
	Constructor();
}

ADSPuzzleActor::~ADSPuzzleActor()
{	
}

void ADSPuzzleActor::Constructor()
{
	Count_Width = 0;
	Count_Height = 0;
	Size_Width = 0;
	Size_Height = 0;
	m_iCurTileIndex = -1;
	m_iNextTileIndex = -1;
	m_fSecToStartMoving = 0.0f;
	PrimaryActorTick.bCanEverTick = true;
}

void ADSPuzzleActor::PuzzleStart(const TArray<FString>& Args)
{
	for (TObjectIterator<ADSPuzzleActor> Itr; Itr; ++Itr)
	{
		ADSPuzzleActor* pPuzzleActor = *Itr;
		if (false == pPuzzleActor->IsValidLowLevel())
			continue;

		pPuzzleActor->PuzzleStart();
	}
}

void ADSPuzzleActor::PuzzleStart()
{
	PuzzlePreparation();
	FindNextTile(m_iNextTileIndex, m_fSecToStartMoving);
}

#if WITH_EDITOR
void ADSPuzzleActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (nullptr == PropertyChangedEvent.Property)
		return;

	if (PropertyChangedEvent.Property->GetFName() != GET_MEMBER_NAME_CHECKED(ADSPuzzleActor, Count_Width) &&
		PropertyChangedEvent.Property->GetFName() != GET_MEMBER_NAME_CHECKED(ADSPuzzleActor, Count_Height) &&
		PropertyChangedEvent.Property->GetFName() != GET_MEMBER_NAME_CHECKED(ADSPuzzleActor, Tiles_In_Puzzle))
		return;

	PuzzlePreparation();
}
#endif

void ADSPuzzleActor::BeginPlay()
{
	Super::BeginPlay();
	DS_Regist_Console_Command(ConsolCommandName_PuzzleStart, &ADSPuzzleActor::PuzzleStart, TEXT("The puzzle begins"));
}

void ADSPuzzleActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	DSClientVariableMgr::Get().UnRegistConsolCommand(ConsolCommandName_PuzzleStart);
}

void ADSPuzzleActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateMove();
}

/*
* 퍼즐 준비
*/
void ADSPuzzleActor::PuzzlePreparation()
{
	const int32 iMaxArrayIndex = Count_Width * Count_Height;
	Tiles_In_Puzzle.Reserve(iMaxArrayIndex);
	Tiles_In_Puzzle.SetNum(iMaxArrayIndex);
	m_iCurTileIndex = -1;
	m_StartPoint.Empty();
	m_EndPoint.Empty();
	m_ClosedTileIndex.Empty();
	for (int32 i = 0; i < iMaxArrayIndex; ++i)
	{
		FDSPuzzleTile& CurTile = Tiles_In_Puzzle[i];
		if (CurTile.TileType == ETileType::StartPoint)
			m_StartPoint.Add(i);
		if (CurTile.TileType == ETileType::EndPoint)
			m_EndPoint.Add(i);
	}

	const int32 iStartPointCount = m_StartPoint.Num();
	if (0 == iStartPointCount || 0 == m_EndPoint.Num())
		return;

	const int32 iStartPoint_ArrayIndex = FMath::Rand() % iStartPointCount;
	if (iStartPoint_ArrayIndex >= m_StartPoint.Num())
		return;

	const int32 iStartArrayIndex_In_Puzzle = m_StartPoint[iStartPoint_ArrayIndex];
	if (iStartArrayIndex_In_Puzzle < 0 || iStartArrayIndex_In_Puzzle >= iMaxArrayIndex)
		return;

	m_iCurTileIndex = iStartArrayIndex_In_Puzzle;
	m_ClosedTileIndex.Add(m_iCurTileIndex);
}

bool ADSPuzzleActor::FindNextTile(int32& iOutNextTileIndex, float& fSecToStartMoving) const
{
	if (false == IsValid_TileIndex(m_iCurTileIndex))
		return false;

	FDSPuzzleTile kNeighborTile;
	for (int32 iDirection = static_cast<int32>(EDirectionOfMove::DownSide); iDirection > static_cast<int32>(EDirectionOfMove::TopSide) ; --iDirection)
	{
		const EDirectionOfMove eDirection = static_cast<EDirectionOfMove>(iDirection);
		const int32 iNeighborTileIndex = GetNeighborTile(eDirection, kNeighborTile);
		if (iNeighborTileIndex < 0)
			continue;

		if (false == IsPossibleToMove(eDirection, iNeighborTileIndex, kNeighborTile))
			continue;

		iOutNextTileIndex = iNeighborTileIndex;
		fSecToStartMoving = DSTimerMgr::Get().GetRealTimeSeconds();
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, FString::Printf(TEXT("%d => %d")
			, m_iCurTileIndex, iOutNextTileIndex), true, FVector2D(2.0f));
		return true;
	}

	return false;
}

int32 ADSPuzzleActor::GetNeighborTile(const EDirectionOfMove eDirection, FDSPuzzleTile& rOutPuzzleTile) const
{
	if (EDirectionOfMove::Max == eDirection)
	{
		return -1;
	}

	int32 iCurX, iCurY;
	if (false == GetXY_By_TileIndex(m_iCurTileIndex, iCurX, iCurY))
		return -1;

	int32 iNeighborX = iCurX;
	int32 iNeighborY = iCurY;
	switch (eDirection)
	{
		case EDirectionOfMove::TopSide:
		{
			iNeighborY = iCurY - 1;
			break;
		}
		case EDirectionOfMove::LeftSide:
		{
			iNeighborX = iCurX - 1;
			break;
		}
		case EDirectionOfMove::RightSide:
		{
			iNeighborX = iCurX + 1;
			break;
		}
		case EDirectionOfMove::DownSide:
		{
			iNeighborY = iCurY + 1;
			break;
		}
		default:
		{
			return -1;
		}
	}


	const int32 iNeighborTileIndex = GetTileIndex_By_XY(iNeighborX, iNeighborY);
	if (false == IsValid_TileIndex(iNeighborTileIndex))
		return -1;

	rOutPuzzleTile = Tiles_In_Puzzle[iNeighborTileIndex];
	return iNeighborTileIndex;
}

bool ADSPuzzleActor::IsPossibleToMove(const EDirectionOfMove eDirection, const int32 iNeighborTileIndex, const FDSPuzzleTile& rNeighborTile) const
{
	if (false == IsValid_TileIndex(m_iCurTileIndex) || false == IsValid_TileIndex(iNeighborTileIndex))
		return false;

	if (m_ClosedTileIndex.Contains(iNeighborTileIndex))
		return false;

	const FDSPuzzleTile& rCurTile = Tiles_In_Puzzle[m_iCurTileIndex];
	if (0 == rCurTile.TileIndex)
		return false;

	const int32 iFromValue = 1 << static_cast<int32>(eDirection);
	const bool bPossible_From = rCurTile.TileIndex & iFromValue;
	if (false == bPossible_From)
		return false;

	const EDirectionOfMove eDirection_To = static_cast<EDirectionOfMove>(static_cast<int32>(EDirectionOfMove::Max) - static_cast<int32>(eDirection) - 1);
	const int32 iToValue = 1 << static_cast<int32>(eDirection_To);
	const bool bPossible_To = rNeighborTile.TileIndex & iToValue;
	return bPossible_To;
}

bool ADSPuzzleActor::IsNeighborTile(const int32 LTileIndex, const int32 RTileIndex) const
{
	if (LTileIndex == RTileIndex)
		return false;

	int32 iLX, iLY, iRX, iRY;
	if (false == GetXY_By_TileIndex(LTileIndex, iLX, iLY) ||
		false == GetXY_By_TileIndex(RTileIndex, iRX, iRY))
		return false;

	bool bSameX = (iLX == iRX);
	bool bSameY = (iLY == iRY);
	if (false == bSameX && false == bSameY)
		return false;

	bool bNeighborX = (FMath::Abs(iLX - iRX) == 1);
	bool bNeighborY = (FMath::Abs(iLY - iRY) == 1);
	return (bSameX && bNeighborY) || (bSameY && bNeighborX);
}

bool ADSPuzzleActor::IsValid_TileIndex(const int32 TileIndex) const
{
	const int32 iMaxArrayIndex = Count_Width * Count_Height;
	if (TileIndex < 0 || TileIndex >= Tiles_In_Puzzle.Num() || TileIndex >= iMaxArrayIndex)
		return false;

	return true;
}

bool ADSPuzzleActor::GetXY_By_TileIndex(const int32 TileIndex, int32& iOutX, int32& iOutY) const
{
	if (false == IsValid_TileIndex(TileIndex))
		return false;

	iOutX = TileIndex % Count_Width;
	iOutY = TileIndex / Count_Width;
	if (iOutY >= Count_Height)
		return false;

	return true;
}

int32 ADSPuzzleActor::GetTileIndex_By_XY(const int32 iX, const int32 iY) const
{
	if (iX < 0 || iY < 0)
		return -1;

	const int32 iCurTileIndex = iY * Count_Width + iX;
	if (false == IsValid_TileIndex(iCurTileIndex))
		return -1;

	return iCurTileIndex;
}

void ADSPuzzleActor::UpdateMove()
{
	if (m_iNextTileIndex < 0)
		return;

	// 이동중일때 
	float fCurSec = DSTimerMgr::Get().GetRealTimeSeconds();
	float fPassedSec = fCurSec - m_fSecToStartMoving;
	if (fPassedSec < SecToGoFromTileToTile || false == IsNeighborTile(m_iCurTileIndex, m_iNextTileIndex))
		return;

	// 목적지에 도착했을대 처리
	m_ClosedTileIndex.Add(m_iCurTileIndex);
	m_iCurTileIndex = m_iNextTileIndex;

	// 최종 목적지에 도착했다면 성공 처리
	if (CheckArrive_FinalDestination())
	{
		return;
	}

	// 다음 목적지 검색
	if (FindNextTile(m_iNextTileIndex, m_fSecToStartMoving))
		return;

	// 이동할수 없을때 실패 처리
	OnMoveFail();
}

void ADSPuzzleActor::OnMoveFail()
{
	m_iNextTileIndex = -1;
	m_fSecToStartMoving = 0.0f;
	GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red
		, FString::Printf(TEXT("Nowhere to go : %d"), m_iCurTileIndex)
		, true, FVector2D(2.0f));
}

bool ADSPuzzleActor::CheckArrive_FinalDestination()
{
	if (false == m_EndPoint.Contains(m_iCurTileIndex))
	{
		return false;
	}

	m_iNextTileIndex = -1;
	m_fSecToStartMoving = 0.0f;
	GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red
		, FString::Printf(TEXT("Arriving at the destination : %d"), m_iCurTileIndex)
		, true, FVector2D(2.0f));
	return true;
}