#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonPlayer;
class PlayerManager : public Singleton<PlayerManager>
{
private:
    PokemonPlayer* player;

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    PokemonPlayer* GetPlayer()
    {
        return player;
    }
    void SetPlayer(PokemonPlayer* player)
    {
        this->player = player;
    }
};
