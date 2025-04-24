#pragma once
#include "Singleton.h"
// clang-format off
#include "config.h"
// clang-format on

class MPlayer;
class PokemonPlayer;
class CollisionManager : public Singleton<CollisionManager>
{
public:
    HRESULT Init();
    void Release();

    void MapPlayerCheck(PokemonPlayer* Player, std::vector<RECT> rcBoxes);

    void MapPlayerCheck(PokemonPlayer* Player, const std::wstring& mapName);

private:
    MPlayer* mPlayer;
};
