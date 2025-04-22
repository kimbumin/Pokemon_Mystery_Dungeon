#pragma once
#include "config.h"
#include "Singleton.h"

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

