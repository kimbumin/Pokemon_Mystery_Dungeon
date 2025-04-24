#pragma once
#include "ISkill.h"
#include "PokemonBase.h"
#include "PokemonPool.h"
#include "Singleton.h"

class PokemonPool;
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
