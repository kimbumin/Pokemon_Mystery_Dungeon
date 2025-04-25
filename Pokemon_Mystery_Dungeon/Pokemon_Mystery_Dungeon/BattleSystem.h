#pragma once
#include "Singleton.h"

#include "config.h"

class PokemonPool;
class PokemonBase;
class ISkill;
class BattleSystem : public Singleton<BattleSystem>
{
private:
    PokemonPool* pokemonPool;

public:
    void SetPokemonPool(PokemonPool* pool);

    int CalculateDamage(PokemonBase* attacker, PokemonBase* target,
                        ISkill* skill);
    PokemonBase* GetTargetInFront(PokemonBase* owner);
};
