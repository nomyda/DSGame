#pragma once

class IManager
{
public:
	virtual ~IManager() {}
	virtual bool Init() { return false; };
	virtual void Release() {};
	virtual void Update() {};
};