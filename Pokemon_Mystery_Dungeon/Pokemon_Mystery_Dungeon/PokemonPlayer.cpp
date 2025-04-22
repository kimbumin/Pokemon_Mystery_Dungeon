#include "PokemonPlayer.h"

#include <cmath>

HRESULT PokemonPlayer::Init()
{
    PokemonBase::Init();
    exp = pow(level, 3);
    expToLevelUp = pow((level + 1), 3);
    return S_OK;
}

void PokemonPlayer::Release()
{
}

void PokemonPlayer::Update()
{
    PokemonBase::Update();
}

bool PokemonPlayer::CanPickUpItem() const
{
    return false;
}

void PokemonPlayer::PickUpItem(Item* item)
{
}

void PokemonPlayer::AddItemToBag(Item* item)
{
}

void PokemonPlayer::UseItem(Item* item)
{
}

void PokemonPlayer::GainExp(int amount)
{
    exp += amount;
    if (exp > expToLevelUp)
    {
        LevelUp();
    }
}

void PokemonPlayer::LevelUp()
{
    // 진화 체크
    ++level;
    expToLevelUp = pow((level + 1), 3);
    CalStatus();
}
