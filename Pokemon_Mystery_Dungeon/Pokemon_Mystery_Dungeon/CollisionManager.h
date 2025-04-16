#pragma once
#include "Singleton.h"
#include "config.h"





class CollisionManager : public Singleton<CollisionManager>
{
public:
	HRESULT Init();
	void Release();





private:

};


