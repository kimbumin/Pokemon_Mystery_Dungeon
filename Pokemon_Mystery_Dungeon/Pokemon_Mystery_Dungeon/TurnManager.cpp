#include "TurnManager.h"

#include "PokemonBase.h"
#include "PokemonPool.h"

void TurnManager::InitTurnOrder(PokemonPool* pokemonPool)
{
    turnOrder = pokemonPool;
}

void TurnManager::Release()
{
    TurnManager::GetInstance()->ReleaseInstance();
}

PokemonBase* TurnManager::GetCurrentPokemon()
{
    int count = 0;
    for (auto iter = turnOrder->begin(); iter != turnOrder->end(); ++iter)
    {
        if (!(*iter)->GetIsAlive())
        {
            continue;
        }

        if (count == currentIndex)
        {
            return *iter;
        }
        ++count;
    }
    return nullptr;
}

bool TurnManager::IsPlayerTurn()
{
    if (currentIndex == 0)
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
    if (!turnOrder || turnOrder->IsEmpty())
    {
        return;
    }

    PokemonBase* current = GetCurrentPokemon();

    switch (state)
    {
        case TurnState::WaitingForInput:

            if (IsPlayerTurn())
            {
                if (KeyManager::GetInstance()->IsOnceKeyDown(
                        VK_UP))  // UI가 어떤 상태이고 그거에 맞는 입력이
                                 // 들어오면(이거도 switch문으로 표현해야할지도)
                {
                    // 플레이어 행동 결정
                    current->ExecuteMoveAction();
                    state = TurnState::ExecutingAction;
                }
                else
                {
                    return;
                }
            }
            else
            {
                // AI 행동 결정
                current->ExecuteMoveAction();
                state = TurnState::ExecutingAction;
            }

            break;

        case TurnState::ExecutingAction:
            if (!IsPlayerTurn())
            {
                state = TurnState::TurnEnd;
                break;
            }
            state = TurnState::WaitingForAnim;
            break;

        case TurnState::WaitingForAnim:
            elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
            if (elapsedTime >= 1.0f)  // Check 고정 시간 대기
            {
                state = TurnState::TurnEnd;
            }
            break;

        case TurnState::TurnEnd:
            ++currentIndex;
            int total = 0;
            for (auto it = turnOrder->begin(); it != turnOrder->end(); ++it)
            {
                if ((*it)->GetIsAlive())
                {
                    ++total;
                }
            }
            if (currentIndex >= total)
            {
                currentIndex = 0;
            }
            state = TurnState::WaitingForInput;
            elapsedTime = 0.0f;
            break;
    }
}