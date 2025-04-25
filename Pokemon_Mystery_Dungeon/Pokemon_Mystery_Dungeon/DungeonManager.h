#pragma once
// clang-format off
#include "config.h"
// clang-format on
class PokemonBuilder;
class PokemonPool;
class Map;

class DungeonManager
{
private:
    // 던전 이름, 던전 정보
    unordered_map<string, DungeonSpawnInfo> dungeonSpawnMap;

    Map* dungeonMap;
    PokemonBuilder* builder;
    PokemonPool* pool;

public:
    void Init();
    void LoadDungeonData();
    void EnterDungeon(string dungeonName);
    void ExitDungeon();

    // Getter
    inline PokemonPool* GetPokemonPool()
    {
        return pool;
    }

    // Setter
    inline void SetDungeonMap(Map* dungeonMap)
    {
        this->dungeonMap = dungeonMap;
    }
    DungeonManager() {};
    virtual ~DungeonManager() {};
};