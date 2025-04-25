#include "CollisionManager.h"

#include "CollisionBoxTool.h"
#include "CommonFunction.h"
#include "PokemonPlayer.h"

HRESULT CollisionManager::Init()
{
    return S_OK;
}

void CollisionManager::Release()
{
    ReleaseInstance();
}
void CollisionManager::MapPlayerCheck(PokemonPlayer* Player,
                                      std::vector<RECT> rcBoxes)
{
    if (!Player)
        return;

    RECT playerRect = Player->GetRect();

    for (const RECT& rc : rcBoxes)
    {
        if (RectInRect(playerRect, rc))
        {
            Player->UndoMove();
            break;
        }
    }
}
void CollisionManager::MapPlayerCheck(PokemonPlayer* Player,
                                      const std::wstring& mapName)
{
}