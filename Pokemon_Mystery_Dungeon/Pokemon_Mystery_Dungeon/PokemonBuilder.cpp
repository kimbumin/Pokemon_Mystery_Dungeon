#include "PokemonBuilder.h"

#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonPool.h"

PokemonBase* PokemonBuilder::Build(int id, int level, FPOINT pos)
{
    PokemonBase* pokemon = pokemonPool->Get();
    if (!pokemon)
    {
        return nullptr;
    }

    const PokemonData* baseData = PokemonDataLoader::GetInstance()->GetData(id);
    if (!baseData)
    {
        return nullptr;
    }

    pokemon->SetStatus(baseData);
    pokemon->SetLevel(level);
    pokemon->SetPos(pos);
    pokemon->SetIsAlive(true);
    pokemon->Init();

    return pokemon;
}

PokemonBase* PokemonBuilder::BuildFromDungeonInfo(DungeonSpawnInfo& info)
{
    int id = RandomChoice(info.pokemonIds);
    int level = RandomRange(info.minLevel, info.maxLevel);
    FPOINT pos = GetRandomValidPosition();  // 유효성 포함된 랜덤 좌표

    return Build(id, level, pos);
}

int PokemonBuilder::RandomChoice(vector<int>& vec)
{
    if (vec.empty())
    {
        return -1;
    }
    return vec[rand() % vec.size()];
}

int PokemonBuilder::RandomRange(int min, int max)
{
    if (min > max)  // 순서 안 중요하게
    {
        swap(min, max);
    }
    return rand() % (max - min + 1) + min;
}

FPOINT PokemonBuilder::GetRandomValidPosition()
{
    while (true)
    {
        int x = rand() % TILE_X;
        int y = rand() % TILE_Y;

        // if (IsWalkable(x, y)) // Check
        if (1)
        {
            return FPOINT{x * TILE_SIZE * 1.0f, y * TILE_SIZE * 1.0f};
        }
    }
}

void PokemonBuilder::SetPool(PokemonPool* newPool)
{
    pokemonPool = newPool;
}