#include "TurnManager.h"

#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "IActionState.h"
#include "IAnimState.h"
#include "ISkill.h"
#include "Map.h"
#include "PlayerManager.h"
#include "PokemonBase.h"
#include "PokemonEnemy.h"
#include "PokemonPlayer.h"
#include "PokemonPool.h"
#include "SkillUIState.h"
#include "UIManager.h"

void TurnManager::InitTurnOrder(PokemonPool* pokemonPool)
{
    turnOrder = pokemonPool;
}

void TurnManager::Release()
{
    turnOrder = nullptr;
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

    if (!current)
    {
        return;
    }

    Map* map = current->GetMap();
    PokemonPool* pool = turnOrder;

    switch (state)
    {
        case TurnState::WaitingForInput:

            if (IsPlayerTurn())
            {
                Direction inputDir;
                bool hasInput = false;
                // Check UI
                if (UIManager::GetInstance()->FindState("SkillUI"))
                {
                    SkillUIState* skillUI = static_cast<SkillUIState*>(
                        UIManager::GetInstance()->FindState("SkillUI"));
                    int index = skillUI->GetSelectedSkillIndex();
                    if (index >= 0 && index < 4)
                    {
                        shared_ptr<ISkill> selectedSkill =
                            PlayerManager::GetInstance()->GetPlayer()->GetSkill(
                                index);
                        current->ExecuteAttackAction(selectedSkill);
                        skillUI->SetSelectedSkillIndex(-1);
                        state = TurnState::WaitingForCompletion;
                    }
                }

                if (UIManager::GetInstance()->GetCurrentStateKey() == "IdleUI")
                {
                    // 버퍼 중이 아닌 상태에서 첫 입력 감지
                    if (!waitingForDiagonal)
                    {
                        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
                        {
                            bufferedDir = Direction::NORTH;
                            waitingForDiagonal = true;
                            bufferElapsed = 0.f;
                        }
                        else if (KeyManager::GetInstance()->IsOnceKeyDown(
                                     VK_DOWN))
                        {
                            bufferedDir = Direction::SOUTH;
                            waitingForDiagonal = true;
                            bufferElapsed = 0.f;
                        }
                        else if (KeyManager::GetInstance()->IsOnceKeyDown(
                                     VK_LEFT))
                        {
                            bufferedDir = Direction::WEST;
                            waitingForDiagonal = true;
                            bufferElapsed = 0.f;
                        }
                        else if (KeyManager::GetInstance()->IsOnceKeyDown(
                                     VK_RIGHT))
                        {
                            bufferedDir = Direction::EAST;
                            waitingForDiagonal = true;
                            bufferElapsed = 0.f;
                        }
                    }

                    // 버퍼 중일 때 대각선 확인
                    if (waitingForDiagonal)
                    {
                        bufferElapsed +=
                            TimerManager::GetInstance()->GetDeltaTime();

                        // 대각선 조합 감지
                        if (bufferedDir == Direction::NORTH)
                        {
                            if (KeyManager::GetInstance()->IsStayKeyDown(
                                    VK_RIGHT))
                            {
                                inputDir = Direction::NORTHEAST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                            else if (KeyManager::GetInstance()->IsStayKeyDown(
                                         VK_LEFT))
                            {
                                inputDir = Direction::NORTHWEST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                        }
                        else if (bufferedDir == Direction::SOUTH)
                        {
                            if (KeyManager::GetInstance()->IsStayKeyDown(
                                    VK_RIGHT))
                            {
                                inputDir = Direction::SOUTHEAST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                            else if (KeyManager::GetInstance()->IsStayKeyDown(
                                         VK_LEFT))
                            {
                                inputDir = Direction::SOUTHWEST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                        }
                        else if (bufferedDir == Direction::EAST)
                        {
                            if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
                            {
                                inputDir = Direction::NORTHEAST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                            else if (KeyManager::GetInstance()->IsStayKeyDown(
                                         VK_DOWN))
                            {
                                inputDir = Direction::SOUTHEAST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                        }
                        else if (bufferedDir == Direction::WEST)
                        {
                            if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
                            {
                                inputDir = Direction::NORTHWEST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                            else if (KeyManager::GetInstance()->IsStayKeyDown(
                                         VK_DOWN))
                            {
                                inputDir = Direction::SOUTHWEST;
                                hasInput = true;
                                waitingForDiagonal = false;
                            }
                        }

                        // 버퍼 초과 시 일반 방향 처리
                        if (bufferElapsed >= inputBufferTime && !hasInput)
                        {
                            inputDir = bufferedDir;
                            hasInput = true;
                            waitingForDiagonal = false;
                        }
                    }

                    // 방향 입력 완료 후 이동 처리
                    if (hasInput)
                    {
                        current->SetDirection(inputDir);

                        FPOINT currentPos = current->GetPos();
                        auto [dx, dy] =
                            directionOffsets[static_cast<int>(inputDir)];
                        int nextX =
                            static_cast<int>(currentPos.x / TILE_SIZE) + dx;
                        int nextY =
                            static_cast<int>(currentPos.y / TILE_SIZE) + dy;

                        if (map && map->IsPathOrFloor(nextX, nextY))
                        {
                            FPOINT nextPos = {nextX * TILE_SIZE * 1.0f,
                                              nextY * TILE_SIZE * 1.0f};

                            if (!pool->IsPositionBlocked(nextPos))
                            {
                                current->ExecuteMoveAction();
                                state = TurnState::WaitingForCompletion;
                            }
                            else
                            {
                                current->ExecuteIdleAction();
                            }
                        }
                        else
                        {
                            current->ExecuteIdleAction();
                        }
                    }
                }
            }

            else  // AI 턴
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

            for (auto iter = turnOrder->begin() + 1; iter != turnOrder->end();
                 ++iter)
            {
                PokemonBase* enemy = *iter;
                if (!enemy->GetIsAlive())
                {
                    enemy->Release();
                    turnOrder->Return(enemy);
                }
            }

           
            ++currentIndex;
            int total = CountAlive();
            if (currentIndex >= total)
            {
                currentIndex = 0;
            }

            state = TurnState::WaitingForInput;
            break;
    }

    PokemonBase* player = PlayerManager::GetInstance()->GetPlayer();
    if (!player->GetIsAlive() && UIManager::GetInstance()->GetCurrentStateKey() == "IdleUI")
    {
        // 씬 전환
        SceneManager::GetInstance()->ChangeScene("Square");

        // 플레이어 부활 처리
        player->SetIsAlive(true);
        player->SetPos({ 500, 300 });
        player->SetHp(player->GetCurrentPokemonData().hp);
        player->Init();

        return;
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