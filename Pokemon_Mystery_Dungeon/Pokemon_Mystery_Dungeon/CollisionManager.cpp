#include "CollisionManager.h"
#include "MPlayer.h"
#include "CommonFunction.h"
#include "CollisionBoxTool.h"

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::Release()
{
	ReleaseInstance();

}
void CollisionManager::MapPlayerCheck(MPlayer* mPlayer, std::vector<RECT> rcBoxes)
{
    if (!mPlayer) return;

    RECT playerRect = mPlayer->GetRect();

    for (const RECT& rc : rcBoxes)
    {
        if (RectInRect(playerRect, rc))
        {
            mPlayer->UndoMove();
            break;
        }
    }
}