#pragma once

/*
* ΩÃ±€≈Ê ∆–≈œ
*/
template<class T>
class DSSingleton
{
public:
	typedef TSharedPtr<T> SharedSingleton;
	static T& Get();
	virtual void OnSingleton() = 0;


protected:	
	DSSingleton() {}
	virtual ~DSSingleton() {}


private:	
	static SharedSingleton m_Instance;
};

template<class T>
TSharedPtr<T> DSSingleton<T>::m_Instance;

#include "DSSingleton.hpp"