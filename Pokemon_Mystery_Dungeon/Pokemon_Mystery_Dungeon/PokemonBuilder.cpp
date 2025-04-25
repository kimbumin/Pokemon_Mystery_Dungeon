#include "PokemonBuilder.h"

#include "Map.h"
#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonPool.h"
#include "SkillManager.h"

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

    shared_ptr<ISkill> skill1 = SkillManager::GetInstance()->CreateSkill("BodySlam");
    shared_ptr<ISkill> skill2;

    if (pokemon->GetCurrentPokemonData().types[0] == "Normal")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("Tackle");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Fighting")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("KneeKick");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Grass")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("PetalDance");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Fire")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("Ember");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Water")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("WaterGun");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Flying")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("WingAttack");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Poison")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("Sludge");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Electric")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("Thunderbolt");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Ground")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("EarthPower");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Rock")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("StoneShower");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Ice")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("IcePunch");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Bug")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("BugBuzz");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Psychic")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("Psychokinesis");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Dragon")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("DragonClaw");
    }
    else if (pokemon->GetCurrentPokemonData().types[0] == "Ghost")
    {
        skill2 = SkillManager::GetInstance()->CreateSkill("ShadowBall");
    }


    if (skill1)
        pokemon->SetSkill(0, skill1);
    if (skill2)
        pokemon->SetSkill(1, skill2);

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

        if (!map || !map->IsPathOrFloor(x, y))
        {
            continue;
        }

        FPOINT pos = {x * TILE_SIZE * 1.0f, y * TILE_SIZE * 1.0f};

        if (pokemonPool && !IsPositionOccupied(pos))
        {
            return pos;
        }
    }
}

bool PokemonBuilder::IsPositionOccupied(FPOINT pos)
{
    for (auto iter = pokemonPool->begin(); iter != pokemonPool->end(); ++iter)
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

void PokemonBuilder::SetPool(PokemonPool* newPool)
{
    pokemonPool = newPool;
}

void PokemonBuilder::SetMap(Map* map)
{
    this->map = map;
}
