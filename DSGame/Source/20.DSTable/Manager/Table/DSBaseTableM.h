#pragma once
#include "Manager/DSBaseM.h"

class UDataTable;

namespace Manager
{
	template<class TableM, class Table>
	class DSTABLE_API DSBaseTableM : public DSBaseM<TableM>
	{
	protected:
		// IManager
		bool Init() override
		{
			Release();

			int32 LoadCount = 0;
			for (auto& Cur : m_ArrayAssetPath)
			{
				LoadCount += LoadTableAsset(Cur);
			}

			return LoadCount > 0;
		}

		bool Release() override
		{
			if (m_WpDataTable.IsValid())
			{
				m_WpDataTable->RemoveFromRoot();
				m_WpDataTable.Reset();
			}

			m_TidAndTable.Reset();
			return true;
		}

		void AddAssetPath(const TCHAR* AssetPath)
		{
			m_ArrayAssetPath.Add(AssetPath);
		}

	private:
		bool LoadTableAsset(const TCHAR* AssetPath)
		{
			m_WpDataTable = LoadObject<UDataTable>(nullptr, AssetPath);
			if (false == m_WpDataTable.IsValid())
				return false;

			m_WpDataTable->AddToRoot();
			const TMap<FName, uint8*>& TidAndTableMap = m_WpDataTable->GetRowMap();
			for (TMap<FName, uint8*>::TConstIterator RowMapIter(TidAndTableMap.CreateConstIterator()); RowMapIter; ++RowMapIter)
			{
				const FName& Tid = RowMapIter.Key();
				if (m_TidAndTable.Contains(Tid))
				{
					ensureMsgf(false, TEXT("Tid %s Exist"), *Tid.ToString());
					continue;
				}

				const Table* CurTable = reinterpret_cast<const Table*>(RowMapIter.Value());
				m_TidAndTable.Add(Tid, CurTable);
			}

			return m_TidAndTable.Num() > 0;
		}

	private:
		typedef TArray<const TCHAR*> ArrayAssetPath;
		ArrayAssetPath m_ArrayAssetPath;
		TWeakObjectPtr<UDataTable> m_WpDataTable;
		TSortedMap<FName, const Table*, FDefaultAllocator, FNameFastLess> m_TidAndTable;
	};
}