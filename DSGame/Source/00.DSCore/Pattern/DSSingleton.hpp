#pragma once

template<class T>
T& DSSingleton<T>::Instance()
{
	if (false == m_Instance.IsValid())
	{
		m_Instance = SharedSingleton(new T);
		m_Instance->OnInstance();
	}

	return *m_Instance.Get();
}