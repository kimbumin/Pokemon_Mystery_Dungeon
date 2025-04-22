#pragma once
#include "config.h"

class PokemonPool;
class PokemonBase;
class PokemonBuilder
{
private:
protected:
    PokemonPool* pokemonPool;

public:
    PokemonBase* Build(int id, int level, FPOINT pos);
    PokemonBase* BuildFromDungeonInfo(DungeonSpawnInfo& info);

    int RandomChoice(vector<int>& v);
    int RandomRange(int min, int max);
    FPOINT GetRandomValidPosition();

    // Setter
    virtual void SetPool(PokemonPool* newPool);

    PokemonBuilder() {};
    virtual ~PokemonBuilder() {};
};