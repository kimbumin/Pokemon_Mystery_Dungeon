#include "PokemonEvolutionDataLoader.h"

#include <fstream>
#include <sstream>

void PokemonEvolutionDataLoader::Init()
{
    evolutionMap.clear();
}

void PokemonEvolutionDataLoader::Release()
{
    PokemonEvolutionDataLoader::GetInstance()->ReleaseInstance();
}

bool PokemonEvolutionDataLoader::LoadFromCSV(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        return false;
    }

    string line;
    getline(file, line);  // 첫 줄 헤더 생략

    while (getline(file, line))
    {
        stringstream stream(line);
        string token;

        EvolutionData data;

        // PokemonID
        getline(stream, token, ',');
        data.basePokemonId = stoi(token);

        // PokemonName (무시)
        getline(stream, token, ',');

        // EvolvesToID
        getline(stream, token, ',');
        data.evolvedPokemonId = stoi(token);

        // EvolvesToName (무시)
        getline(stream, token, ',');

        // LevelRequired
        getline(stream, token, ',');
        if (token.empty() || stoi(token) <= 0)
        {
            continue;  // 레벨 진화 아닌 경우 무시
        }

        data.requiredLevel = stoi(token);

        evolutionMap[data.basePokemonId] = data;
    }

    return true;
}

EvolutionData* PokemonEvolutionDataLoader::GetData(int idNumber)
{
    auto iter = evolutionMap.find(idNumber);
    return (iter != evolutionMap.end()) ? &iter->second : nullptr;
}

unordered_map<int, EvolutionData>& PokemonEvolutionDataLoader::GetAllData()
{
    return evolutionMap;
}

