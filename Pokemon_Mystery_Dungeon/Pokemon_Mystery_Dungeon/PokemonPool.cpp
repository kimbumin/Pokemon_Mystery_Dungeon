#include "PokemonPool.h"

#include "PlayerManager.h"
#include "PokemonBase.h"
#include "PokemonEnemy.h"
#include "PokemonPlayer.h"

HRESULT PokemonPool::Init()
{
    pokemonPool.resize(20);
    pokemonPool[0] = PlayerManager::GetInstance()->GetPlayer();
    for (iterPokemonPool = begin(); iterPokemonPool != end(); ++iterPokemonPool)
    {
        if (iterPokemonPool == begin())
        {
            continue;
        }
        (*iterPokemonPool) = new PokemonEnemy;
        (*iterPokemonPool)->SetIsAlive(false);
    }
    return S_OK;
}

void PokemonPool::Release()
{
    for (iterPokemonPool = begin() + 1; iterPokemonPool != end();
         ++iterPokemonPool)
    {
        if (iterPokemonPool == begin())
        {
            continue;
        }
        delete (*iterPokemonPool);
        (*iterPokemonPool) = nullptr;
    }
}

void PokemonPool::Update()
{
    for (iterPokemonPool = begin(); iterPokemonPool != end(); ++iterPokemonPool)
    {
        if ((*iterPokemonPool)->GetIsAlive())
        {
            (*iterPokemonPool)->Update();
        }
    }
}

void PokemonPool::Render(HDC hdc)
{
    for (iterPokemonPool = begin(); iterPokemonPool != end(); ++iterPokemonPool)
    {
        if ((*iterPokemonPool)->GetIsAlive())
        {
            (*iterPokemonPool)->Render(hdc);
        }
    }
}

PokemonBase* PokemonPool::Get()
{
    for (int i = 1; i < pokemonPool.size(); ++i)
    {
        if (!pokemonPool[i]->GetIsAlive())
        {
            return pokemonPool[i];
        }
    }
    return nullptr;
}

void PokemonPool::Return(PokemonBase* pokemon)
{
    if (pokemon)
    {
        pokemon->SetIsAlive(false);
    }
}

void PokemonPool::ReturnEnemies()
{
    for (int i = 1; i < pokemonPool.size(); ++i)
    {
        if (pokemonPool[i]->GetIsAlive())
        {
            pokemonPool[i]->SetIsAlive(false);
        }
    }
}

bool PokemonPool::IsEmpty()
{
    for (const auto& pokemon : pokemonPool)
    {
        if (pokemon && pokemon->GetIsAlive())
        {
            return false;
        }
    }
    return true;
}

bool PokemonPool::IsPositionBlocked(FPOINT pos)
{
    for (auto iter = pokemonPool.begin(); iter != pokemonPool.end(); ++iter)
    {
        if ((*iter)->GetIsAlive())
        {
            FPOINT otherPos = (*iter)->GetPos();
            if (abs(pos.x - otherPos.x) < TILE_SIZE &&
                abs(pos.y - otherPos.y) < TILE_SIZE)
            {
                return true;
            }
        }
    }
    return false;
}

// 동료가 생기는 상황에서는 구조 개편이 많이 필요할것 같다