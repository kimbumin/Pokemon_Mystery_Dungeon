#include "TurnManager.h"

#include "IActionState.h"
#include "PokemonBase.h"
#include "PokemonEnemy.h"
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
                if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
                // UI가 어떤 상태이고 그거에 맞는 입력이
                // 들어오면(이거도 switch문으로 표현해야할지도)
                {
                    current->SetDirection(Direction::NORTH);
                    current->ExecuteMoveAction();
                    state = TurnState::WaitingForCompletion;
                }
                if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
                {
                    current->SetDirection(Direction::SOUTH);
                    current->ExecuteMoveAction();
                    state = TurnState::WaitingForCompletion;
                }
                if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
                {
                    current->SetDirection(Direction::WEST);
                    current->ExecuteMoveAction();
                    state = TurnState::WaitingForCompletion;
                }
                if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
                {
                    current->SetDirection(Direction::EAST);
                    current->ExecuteMoveAction();
                    state = TurnState::WaitingForCompletion;
                }
            }
            else
            {
                current->ExecuteTurn();
                state = TurnState::WaitingForCompletion;
            }
            break;

        case TurnState::WaitingForCompletion:
            if (current->GetCurrentActionState()->IsFinished())
            {
                state = TurnState::TurnEnd;
            }
            break;

        case TurnState::TurnEnd:
            ++currentIndex;
            int total = CountAlive();
            if (currentIndex >= total)
                currentIndex = 0;

            state = TurnState::WaitingForInput;
            break;
    }
}
int TurnManager::CountAlive()
{
    int count = 0;
    for (auto it = turnOrder->begin(); it != turnOrder->end(); ++it)
    {
        if ((*it)->GetIsAlive())
        {
            ++count;
        }
    }
    return count;
}