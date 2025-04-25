#include "BattleSystem.h"

#include "config.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "CommonFunction.h"
#include "ISkill.h"
#include "PokemonPool.h"
#include "PokemonBase.h"

void BattleSystem::SetPokemonPool(PokemonPool* pool)
{
    pokemonPool = pool;
}

int BattleSystem::CalculateDamage(PokemonBase* attacker, PokemonBase* target,
                                  ISkill* skill)
{
    DialogueManager::GetInstance()->ShowLine(
        DialogueTemplate::UsedSkill,
        {
            {L"userName", ToWString(attacker->GetCurrentPokemonData().name)},
            {L"skillName", ToWString(skill->GetName())}
        }
    );

    int power = skill->GetPower();              // Skill power
    string skillType = skill->GetSkillType();   // "Physical" or "Special"
    string skillElement = skill->GetElement();  // "Fire", "Water", etc.

    const PokemonData& atkData = attacker->GetCurrentPokemonData();
    const PokemonData& defData = target->GetCurrentPokemonData();

    int level = attacker->GetLevel();

    int atkStat = (skillType == "Physical") ? atkData.atk : atkData.spAtk;
    int defStat = (skillType == "Physical") ? defData.def : defData.spDef;

    float typeBonus = 1.0f;
    for (const auto& t : atkData.types)
    {
        if (t == skillElement)
        {
            typeBonus = 1.5f;
            break;
        }
    }

    float typeEffect = 1.0f;
    for (const auto& defType : defData.types)
    {
        if (skillElement == "Fire")
        {
            if (defType == "Grass" || defType == "Ice" || defType == "Bug")
                typeEffect *= 2.0f;
            else if (defType == "Fire" || defType == "Water" ||
                     defType == "Rock")
                typeEffect *= 0.5f;
        }
        else if (skillElement == "Water")
        {
            if (defType == "Fire" || defType == "Rock" || defType == "Ground")
                typeEffect *= 2.0f;
            else if (defType == "Water" || defType == "Grass" ||
                     defType == "Dragon")
                typeEffect *= 0.5f;
        }
        else if (skillElement == "Electric")
        {
            if (defType == "Water" || defType == "Flying")
                typeEffect *= 2.0f;
            else if (defType == "Electric" || defType == "Grass" ||
                     defType == "Dragon")
                typeEffect *= 0.5f;
            else if (defType == "Ground")
                typeEffect *= 0.0f;
        }
        else if (skillElement == "Grass")
        {
            if (defType == "Water" || defType == "Ground" || defType == "Rock")
                typeEffect *= 2.0f;
            else if (defType == "Fire" || defType == "Grass" ||
                     defType == "Flying")
                typeEffect *= 0.5f;
        }
    }

    float randomRate = (rand() % 16 + 85) / 100.0f;

    float modifier = typeBonus * typeEffect * randomRate;

    float damage =
        (((((2.0f * level) / 5.0f + 2.0f) * power * atkStat) / defStat) /
             50.0f +
         2.0f) *
        modifier;

    return static_cast<int>(damage);
}


PokemonBase* BattleSystem::GetTargetInFront(PokemonBase* owner)
{
    FPOINT pos = owner->GetPos();
    int dir = static_cast<int>(owner->GetDirection());

    FPOINT frontPos = {pos.x + directionOffsets[dir].first * TILE_SIZE,
                       pos.y + directionOffsets[dir].second * TILE_SIZE};

    for (auto iter = pokemonPool->begin(); iter != pokemonPool->end(); ++iter)
    {
        PokemonBase* target = *iter;
        if (target == owner)
        {
            continue;
        }
        if (!target->GetIsAlive())
        {
            continue;
        }
        FPOINT targetPos = target->GetPos();
        if (abs(targetPos.x - frontPos.x) < TILE_SIZE &&
            abs(targetPos.y - frontPos.y) < TILE_SIZE)
        {
            return target;
        }
    }

    return nullptr;
}