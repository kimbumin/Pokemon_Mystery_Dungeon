#pragma once
#include "Singleton.h"
#include "config.h"


class MPlayer;

class CollisionManager : public Singleton<CollisionManager>
{
public:
	HRESULT Init();
	void Release();

	void MapPlayerCheck(MPlayer* mPlayer, std::vector<RECT> rcBoxes);

	void MapPlayerCheck(MPlayer* mPlayer, const std::wstring& mapName);


private:
	MPlayer* mPlayer;

};


