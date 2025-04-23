#include "BattleSystem.h"

#include "config.h"

void BattleSystem::SetPokemonPool(PokemonPool* pool)
{
    pokemonPool = pool;
}

int BattleSystem::CalculateDamage(PokemonBase* attacker, PokemonBase* target,
                                  ISkill* skill)
{
    int power = skill->GetPower();              // SkillPower
    string skillType = skill->GetSkillType();   // "Physical" or "Special"
    string skillElement = skill->GetElement();  // "Fire", "Water" ..

    const PokemonData& atkData =
        attacker->GetCurrentPokemonData();  // attacker atkData
    const PokemonData& defData =
        target->GetCurrentPokemonData();  // target defData

    int atkStat = (skillType == "Physical")
                      ? atkData.atk
                      : atkData.spAtk;  // Atk Physical Cheak
    int defStat = (skillType == "Physical")
                      ? defData.def
                      : defData.spDef;  // Def Physical Cheak

    float typeBonus = 1.0f;  // Same Type Attack Bonus
    for (const auto& t : atkData.types)
    {
        if (t == skillElement)
        {
            typeBonus = 1.5f;
            break;
        }
    }

    float typeEffect = 1.0f;  // ElementTypeEffectiveness Hardcoding
    for (const auto& defType : defData.types)
    {
        if (skillElement == "Fire")
        {
            if (defType == "Grass" || defType == "Ice" || defType == "Bug")
            {
                typeEffect *= 2.0f;
            }
            else if (defType == "Fire" || defType == "Water" ||
                     defType == "Rock")
            {
                typeEffect *= 0.5f;
            }
        }
        else if (skillElement == "Water")
        {
            if (defType == "Fire" || defType == "Rock" || defType == "Ground")
            {
                typeEffect *= 2.0f;
            }
            else if (defType == "Water" || defType == "Grass" ||
                     defType == "Dragon")
            {
                typeEffect *= 0.5f;
            }
        }
        else if (skillElement == "Electric")
        {
            if (defType == "Water" || defType == "Flying")
            {
                typeEffect *= 2.0f;
            }
            else if (defType == "Electric" || defType == "Grass" ||
                     defType == "Dragon")
            {
                typeEffect *= 0.5f;
            }
            else if (defType == "Ground")
            {
                typeEffect *= 0.0f;
            }
        }
        else if (skillElement == "Grass")
        {
            if (defType == "Water" || defType == "Ground" || defType == "Rock")
            {
                typeEffect *= 2.0f;
            }
            else if (defType == "Fire" || defType == "Grass" ||
                     defType == "Flying")
            {
                typeEffect *= 0.5f;
            }
        }
    }

    float randomRate = (rand() % 71 + 10) / 100.0f;

    float totalDamage = ((atkStat * power) / (float)defStat) * typeBonus *
                        typeEffect * randomRate;

    return static_cast<int>(totalDamage);
}

PokemonBase* BattleSystem::GetTargetInFront(PokemonBase* owner)
{
    FPOINT pos = owner->GetPos();
    int dir = static_cast<int>(owner->GetDirection());

    FPOINT frontPos = {
        pos.x + directionOffsets[dir].first * TILE_SIZE,
        pos.y + directionOffsets[dir].second * TILE_SIZE
    };

    for (auto iter = pokemonPool->begin(); iter != pokemonPool->end(); ++iter)
    {
        PokemonBase* target = *iter;
        if (target == owner) continue;
        if (!target->GetIsAlive()) continue;

        FPOINT targetPos = target->GetPos();
        if (abs(targetPos.x - frontPos.x) < TILE_SIZE &&
            abs(targetPos.y - frontPos.y) < TILE_SIZE)
        {
            return target;
        }
    }

    return nullptr;
}


// Skill Use(Owner) Change
//     PokemonBase* target =
//     BattleSystem::GetInstance()->GetTargetInFront(owner);
// if (target)
//{
//     int damage =
//         BattleSystem::GetInstance()->CalculateDamage(owner, target, this);
//     target->TakeDamage(damage);
// }