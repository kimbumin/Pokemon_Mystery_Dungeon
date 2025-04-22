#pragma once
#include "Singleton.h"
// clang-format off
#include "config.h"
// clang-format on

class PokemonDataLoader : public Singleton<PokemonDataLoader>
{
private:
    unordered_map<int, PokemonData> baseDataMap;

public:
    void Init();
    void Release();
    bool LoadFromCSV(const string& filepath);

    // Getter
    PokemonData* GetData(int idNumber);
    unordered_map<int, PokemonData>& GetAllData();
};