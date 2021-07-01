#include "DSUe4Mgr.h"

DSUe4Mgr::DSUe4Mgr()
{

}

DSUe4Mgr::~DSUe4Mgr()
{

}

EMgrIndex DSUe4Mgr::GetIndex() const
{
	return EMgrIndex::Ue4;
}

void DSUe4Mgr::SetGameInstance(UGameInstance* pGameInstance)
{
	m_wpGameInstance = WeakGameInstancePtr(pGameInstance);
}

UGameInstance* DSUe4Mgr::GetGameInstance()
{
	if (false == m_wpGameInstance.IsValid())
		return nullptr;

	return m_wpGameInstance.Get();
}

UWorld* DSUe4Mgr::GetWorld()
{
	if (nullptr == GEngine)
		return nullptr;

	const FWorldContext* pWorldContext = nullptr;
	for (const FWorldContext& Context : GEngine->GetWorldContexts())
	{
		pWorldContext = &Context;
		if (nullptr == pWorldContext->OwningGameInstance)
			continue;

		UWorld* pWorld = pWorldContext->World();
		if (nullptr == pWorld)
			continue;

		if (pWorld->bIsTearingDown)
			continue;

		return pWorld;
	}

	return nullptr;
}

APlayerController* DSUe4Mgr::GetCurrentPlayerController()
{
	UWorld* pWorld = GetWorld();
	if (nullptr == pWorld)
		return nullptr;

	return pWorld->GetFirstPlayerController();
}