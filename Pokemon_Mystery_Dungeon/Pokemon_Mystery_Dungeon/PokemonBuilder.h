#pragma once
// clang-format off
#include "config.h"
// clang-format on

class PokemonPool;
class PokemonBase;
class Map;
class PokemonBuilder
{
private:
protected:
    PokemonPool* pokemonPool;
    Map* map;
public:
    PokemonBase* Build(int id, int level, FPOINT pos);
    PokemonBase* BuildFromDungeonInfo(DungeonSpawnInfo& info);

    int RandomChoice(vector<int>& v);
    int RandomRange(int min, int max);
    FPOINT GetRandomValidPosition();

    // Setter
    virtual void SetPool(PokemonPool* newPool);
    virtual void SetMap(Map* map);
    PokemonBuilder() {};
    virtual ~PokemonBuilder() {};
};