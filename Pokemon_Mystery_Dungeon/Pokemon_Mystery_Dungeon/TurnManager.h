#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonBase;
class PokemonPool;
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
    PokemonPool* turnOrder;
    int currentIndex = 0;
    TurnState state = TurnState::WaitingForInput;
    float elapsedTime = 0.f;

public:
    void InitTurnOrder(PokemonPool* pokemonPool);
    void Release();
    void Update();

    PokemonBase* GetCurrentPokemon();
    bool IsPlayerTurn();
    TurnState GetState()
    {
        return state;
    }
};
