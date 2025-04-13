#pragma once
#include "config.h"

class PokemonImageLoader
{
private:
	unordered_set<string> loadedImageKeys;

	const vector<string> animTypes = { "Attack", "Hurt", "Idle", "Rotate", "Swing", "Walk" };

public:
	void BeginDungeon(const string& dungeonName);
	void LoadPokemonAnim(int pokemonId);
	void EndDungeon();

	string PokemonIdToString(int pokemonId);
};

