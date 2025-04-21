#include "TurnManager.h"
#include "PokemonBase.h"

void TurnManager::InitTurnOrder(vector<PokemonBase*>& pokemons)
{
}

PokemonBase* TurnManager::GetCurrentPokemon()
{
    return turnOrder[currentIndex];
}

bool TurnManager::IsPlayerTurn()
{
    if (currentIndex = 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TurnManager::Update()
{
    if (turnOrder.empty()) 
    {
        return;
    }

    PokemonBase* current = GetCurrentPokemon();

    switch (state)
    {
    case TurnState::WaitingForInput:
        /*
        if (플레이어차례) IsPlayerTurn()
        {
            if(유효한 입력을 하면)
            {
            // 플레이어 행동 결정
                state = TurnState::ExecutingAction;

            }
        }
        else
        {
            // AI 행동 결정
            state = TurnState::ExecutingAction;
        }
        */  
        break;

    case TurnState::ExecutingAction:
        state = TurnState::WaitingForAnim;
        break;

    case TurnState::WaitingForAnim:
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
        if (elapsedTime >= 1.0f) // Check 고정 시간 대기
        {
            state = TurnState::TurnEnd;
        }
        break;

    case TurnState::TurnEnd:
        ++ currentIndex;
        state = TurnState::WaitingForInput;
        // 한 턴 경과
        break;
    }
}