#include "PokemonDataLoader.h"
#include <fstream>
#include <sstream>


void PokemonDataLoader::Init()
{
    baseDataMap.clear();
}

bool PokemonDataLoader::LoadFromCSV(string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // 첫 줄 생략

    while (getline(file, line)) 
    {
        stringstream stream(line);
        string token;

        PokemonData data;

        getline(stream, token, ',');
        data.idNumber = stoi(token);
        getline(stream, data.name, ',');

        // 능력치들
        stream >> data.hp >> data.atk >> data.def >> data.spAtk >> data.spDef >> data.speed >> data.sum >> data.average;

        // 타입1, 타입2
        getline(stream, token, ',');
        if (!token.empty()) data.types.push_back(token);
        getline(stream, token, ',');
        if (!token.empty()) data.types.push_back(token);

        baseDataMap[data.idNumber] = data;
    }

    return true;
}

PokemonData* PokemonDataLoader::GetData(int idNumber)
{
    auto iter = baseDataMap.find(idNumber);
    return (iter != baseDataMap.end()) ? &iter->second : nullptr;
}

unordered_map<int, PokemonData>& PokemonDataLoader::GetAllData()
{
    return baseDataMap;
}
