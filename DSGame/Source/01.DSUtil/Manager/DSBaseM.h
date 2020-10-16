#pragma once
#include "IManager.h"

namespace Manager
{
	template<class T>
	class DSBaseM : public IManager
	{
	public:
		static T& GetM()
		{
			return m_DetailM;
		}

	protected:
		DSBaseM() : IManager()
		{
			if (false == m_bCreate)
			{
				int32 Index = static_cast<int32>(m_DetailM.GetIndex());
				IManager::ms_DetailM[Index] = &m_DetailM;
				m_bCreate = true;
			}
		}
		virtual ~DSBaseM() {}

	private:
		static T m_DetailM;
		static bool m_bCreate;
	};

	template<class T>
	T DSBaseM<T>::m_DetailM;

	template<class T>
	bool DSBaseM<T>::m_bCreate = false;
}