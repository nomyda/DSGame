#include "DSPawn.h"
#include "Manager/Table/DSActorTableM.h"
#include "Table/Actor/DSActorTable.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"

static const float CapsuleRadius = 20.0f;
static const float CapsuleHeight = 88.0f;
static const float RelativeYaw = -90.0f;
ADSPawn::ADSPawn()
	: Super()
	, m_AsyncLoadID_ActorModel(0)
	, m_AsyncLoadID_AnimBP(0)
{
	Constructor();
}

ADSPawn::ADSPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_AsyncLoadID_ActorModel(0)
	, m_AsyncLoadID_AnimBP(0)
{
	Constructor();
}

ADSPawn::~ADSPawn()
{

}

void ADSPawn::BeginPlay()
{
	Super::BeginPlay();
	InitActor();
}

void ADSPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADSPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADSPawn::Constructor()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(CapsuleRadius, CapsuleHeight);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;
	
	ActorModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ActorModel"));
	ActorModel->SetupAttachment(RootComponent);
	static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
	ActorModel->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
	ActorModel->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	ActorModel->SetCollisionProfileName(MeshCollisionProfileName);
	ActorModel->SetGenerateOverlapEvents(false);
	ActorModel->SetCanEverAffectNavigation(false);
	ActorModel->bUseRefPoseOnInitAnim = true;
	ActorModel->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -CapsuleHeight), FRotator(0.0f, RelativeYaw, 0.0f));
}

bool ADSPawn::InitActor()
{	
	DSActorTableM::Get().GetTable(ActorTid, DSActorTableM::TDelegate_GetTable::CreateUObject(this, &ADSPawn::OnGetTable));
	return true;
}

void ADSPawn::OnGetTable(const FDSActorTable* pTable)
{
	if (nullptr == pTable)
		return;

	m_AsyncLoadID_ActorModel = DSAsyncLoadingMgr::Get().RequestAsyncLoading(pTable->ModelMesh.ToSoftObjectPath(), FOnLoadingComplete::CreateUObject(this, &ADSPawn::OnLoadingComplete));
	m_AsyncLoadID_AnimBP = DSAsyncLoadingMgr::Get().RequestAsyncLoading(pTable->AnimBP.ToSoftObjectPath(), FOnLoadingComplete::CreateUObject(this, &ADSPawn::OnLoadingComplete));
}

void ADSPawn::OnLoadingComplete(const uint32 AsyncLoadID, UObject* pLoadedAsset)
{
	if (nullptr == pLoadedAsset)
		return;

	if (m_AsyncLoadID_ActorModel == AsyncLoadID && ActorModel)
	{
		USkeletalMesh* pMesh = Cast<USkeletalMesh>(pLoadedAsset);
		ActorModel->SetSkeletalMesh(pMesh);
		return;
	}

	if (m_AsyncLoadID_AnimBP == AsyncLoadID && ActorModel)
	{
		ActorModel->SetAnimationMode(EAnimationMode::AnimationBlueprint);		
		UAnimBlueprint* pAnimBP = Cast<UAnimBlueprint>(pLoadedAsset);
		if (pAnimBP)
			ActorModel->SetAnimInstanceClass(pAnimBP->GeneratedClass);
		return;
	}
}