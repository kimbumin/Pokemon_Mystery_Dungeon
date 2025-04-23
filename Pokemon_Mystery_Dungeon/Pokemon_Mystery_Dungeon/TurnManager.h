#pragma once
#include "Singleton.h"
#include "config.h"

class PokemonBase;
class PokemonPool;
enum class TurnState
{
    WaitingForInput,
    WaitingForCompletion,
    TurnEnd
};

class TurnManager : public Singleton<TurnManager>
{
private:
    PokemonPool* turnOrder;
    int currentIndex = 0;
    TurnState state = TurnState::WaitingForInput;
    float elapsedTime = 0.f;

    // input buffer
    float inputBufferTime = 0.1f;  // 100ms
    float bufferElapsed = 0.f;
    bool waitingForDiagonal = false;
    Direction bufferedDir;

public:
    void InitTurnOrder(PokemonPool* pokemonPool);
    void Release();
    void Update();

    PokemonBase* GetCurrentPokemon();
    bool IsPlayerTurn();
    int CountAlive();
    TurnState GetState()
    {
        return state;
    }
    PokemonPool* GetPool()
    {
        return turnOrder;
    }
};
