#pragma once
#include "GameFramework/Pawn.h"
#include "Manager/AsyncLoading/DSAsyncLoadingMgr.h"
#include "DSPawn.generated.h"

/**
 *
 */
struct FDSActorTable;
class UCapsuleComponent;
UCLASS()
class DSACTOR_API ADSPawn : public APawn
{
	GENERATED_BODY()

public:
	ADSPawn();
	ADSPawn(const FObjectInitializer& ObjectInitializer);
	virtual ~ADSPawn();

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaSeconds) override;

	void Constructor();
	bool InitActor();
	void OnGetTable(const FDSActorTable* pTable);
	void OnLoadingComplete(const uint32 AsyncLoadID, UObject* pLoadedAsset);

private:
	UPROPERTY(Category = Info, EditAnywhere) FName ActorTid;
	UPROPERTY(Category = Info, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) UCapsuleComponent* CapsuleComponent;
	UPROPERTY(Category = Info, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) USkeletalMeshComponent* ActorModel;
	uint32 m_AsyncLoadID_ActorModel;
	uint32 m_AsyncLoadID_AnimBP;
};