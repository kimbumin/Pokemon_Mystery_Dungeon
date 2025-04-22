#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonImageLoader : public Singleton<PokemonImageLoader>
{
private:
    unordered_set<string> loadedImageKeys;

public:
    void Release();
    void LoadPokemonAnim(int pokemonId);
    void ClearPokemonImage();

    string PokemonIdToString(int pokemonId);
};
