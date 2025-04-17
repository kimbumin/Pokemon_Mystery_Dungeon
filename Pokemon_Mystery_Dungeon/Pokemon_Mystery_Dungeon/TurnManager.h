#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonBase;
enum class TurnState
{
    WaitingForInput,
    ExecutingAction,
    WaitingForAnim,
    TurnEnd
};

class TurnManager : public Singleton<TurnManager>
{
private:

    vector<PokemonBase*> turnOrder;
    int currentIndex = 0;
    TurnState state = TurnState::WaitingForInput;
    float elapsedTime = 0.f;

public:

    void InitTurnOrder(vector<PokemonBase*>& pokemons);
    void Update();

    PokemonBase* GetCurrentPokemon();
    bool IsPlayerTurn();
    TurnState GetState(){ return state; }
};

