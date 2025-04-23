#include "PokemonEnemy.h"

#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "AttackActionState.h"
#include "AttackAnimState.h"
#include "HurtActionState.h"
#include "HurtAnimState.h"
#include "IdleActionState.h"
#include "IdleAnimState.h"
#include "Map.h"
#include "MoveActionState.h"
#include "PlayerManager.h"
#include "PokemonBase.h"
#include "PokemonPlayer.h"
#include "PokemonPool.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "TurnManager.h"
#include "WalkAnimState.h"
HRESULT PokemonEnemy::Init()
{
    return PokemonBase::Init();
}

void PokemonEnemy::Release()
{
}

void PokemonEnemy::Update()
{
    if (currentAnimState)
    {
        currentAnimState->Update(this);
    }
    if (currentActionState && currentActionState->IsFinished())
    {
        SetActionState(idleAction);
    }
    if (currentActionState)
    {
        currentActionState->Update(this);
    }
}

void PokemonEnemy::ExecuteTurn()
{
    FPOINT myPos = this->GetPos();
    FPOINT playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();

    int myX = myPos.x / TILE_SIZE;
    int myY = myPos.y / TILE_SIZE;
    int playerX = playerPos.x / TILE_SIZE;
    int playerY = playerPos.y / TILE_SIZE;

    int dist = max(abs(myX - playerX), abs(myY - playerY));

    this->SetDirection(CalculateDirection(playerPos));

    PokemonPool* pool = TurnManager::GetInstance()->GetPool();
    if (!pool || !dungeonMap)
    {
        return;
    }

    if (dist <= 1)
    {
        // ExecuteAttackAction(nullptr);
        ExecuteIdleAction();
    }
    else if (dist <= 3)
    {
        auto path = AStarPathfinding(myX, myY, playerX, playerY);
        if (!path.empty())
        {
            FPOINT nextPos = path[1];  // path[0] == 현재 위치
            int tileX = static_cast<int>(nextPos.x / TILE_SIZE);
            int tileY = static_cast<int>(nextPos.y / TILE_SIZE);

            if (!pool->IsPositionBlocked(nextPos) &&
                dungeonMap->IsPathOrFloor(tileX, tileY))
            {
                SetDirection(CalculateDirection(nextPos));
                ExecuteMoveAction();
            }
            else
            {
                ExecuteIdleAction();
            }
        }
        else
        {
            ExecuteIdleAction();  // 추적 실패 시 대기
        }
    }
    else
    {
        Direction randomDir = GetRandomWalkableDirection();
        auto [dx, dy] = directionOffsets[static_cast<int>(randomDir)];
        FPOINT nextPos = {pos.x + dx * TILE_SIZE, pos.y + dy * TILE_SIZE};

        if (!pool->IsPositionBlocked(nextPos) &&
            dungeonMap->IsPathOrFloor((int)(nextPos.x / TILE_SIZE),
                                      (int)(nextPos.y / TILE_SIZE)))
        {
            SetDirection(randomDir);
            ExecuteMoveAction();
        }
        else
        {
            ExecuteIdleAction();
        }
    }
}

vector<FPOINT> PokemonEnemy::AStarPathfinding(int startX, int startY, int goalX,
                                              int goalY)
{
    if (!dungeonMap)
    {
        return {};
    }

    priority_queue<pair<float, pair<int, int>>,
                   vector<pair<float, pair<int, int>>>, greater<>>
        openSet;
    set<pair<int, int>> closedSet;
    map<pair<int, int>, pair<int, int>> cameFrom;
    map<pair<int, int>, float> gScore;

    pair<int, int> start = {startX, startY};
    pair<int, int> goal = {goalX, goalY};

    gScore[start] = 0.0f;
    openSet.push({Heuristic(startX, startY, goalX, goalY), start});

    pair<int, int> closestToGoal = start;
    float closestDistance = Heuristic(startX, startY, goalX, goalY);

    while (!openSet.empty())
    {
        pair<int, int> current = openSet.top().second;
        openSet.pop();

        if (current == goal)
        {
            return ReconstructPath(cameFrom, current.first, current.second,
                                   startX, startY);
        }

        closedSet.insert(current);

        for (int i = 0; i < 8; ++i)
        {
            int dx = directionOffsets[i].first;
            int dy = directionOffsets[i].second;
            int nextX = current.first + dx;
            int nextY = current.second + dy;
            pair<int, int> neighbor = {nextX, nextY};

            if (!dungeonMap->IsPathOrFloor(nextX, nextY) ||
                closedSet.count(neighbor))
            {
                continue;
            }

            if (dx != 0 && dy != 0)  // 대각선 이동 시 벽 체크
            {
                int adjX1 = current.first + dx;
                int adjY1 = current.second;
                int adjX2 = current.first;
                int adjY2 = current.second + dy;

                if (!dungeonMap->IsPathOrFloor(adjX1, adjY1) ||
                    !dungeonMap->IsPathOrFloor(adjX2, adjY2))
                {
                    continue;
                }
            }

            float tentativeG = gScore[current] + 1.0f;

            if (!gScore.count(neighbor) || tentativeG < gScore[neighbor])
            {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeG;
                float fScore =
                    tentativeG + Heuristic(nextX, nextY, goalX, goalY);
                openSet.push({fScore, neighbor});

                // 목표에 더 가까운 노드 갱신
                float distToGoal = Heuristic(nextX, nextY, goalX, goalY);
                if (distToGoal < closestDistance)
                {
                    closestDistance = distToGoal;
                    closestToGoal = neighbor;
                }
            }
        }
    }

    return {};
}
float PokemonEnemy::Heuristic(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

vector<FPOINT> PokemonEnemy::ReconstructPath(
    map<pair<int, int>, pair<int, int>>& cameFrom, int goalX, int goalY,
    int startX, int startY)
{
    vector<FPOINT> path;
    pair<int, int> current = {goalX, goalY};

    // 시작 노드 포함
    while (cameFrom.find(current) != cameFrom.end())
    {
        FPOINT worldPos = {current.first * TILE_SIZE * 1.0f,
                           current.second * TILE_SIZE * 1.0f};
        path.insert(path.begin(), worldPos);
        current = cameFrom[current];
    }

    // 마지막으로 시작점 추가
    FPOINT startPos = {startX * TILE_SIZE * 1.0f, startY * TILE_SIZE * 1.0f};
    path.insert(path.begin(), startPos);

    return path;
}

Direction PokemonEnemy::GetRandomWalkableDirection()
{
    vector<Direction> possibleDirs;

    for (int i = 0; i < 8; ++i)
    {
        int nextX =
            static_cast<int>(pos.x / TILE_SIZE) + directionOffsets[i].first;
        int nextY =
            static_cast<int>(pos.y / TILE_SIZE) + directionOffsets[i].second;

        if (dungeonMap != nullptr)
        {
            if (dungeonMap->IsPathOrFloor(nextX, nextY))
            {
                possibleDirs.push_back(static_cast<Direction>(i));
            }
        }
    }

    if (possibleDirs.empty())
    {
        return GetDirection();  // 이동 못하면 현재 방향 유지
    }

    int randomIndex = rand() % possibleDirs.size();
    return possibleDirs[randomIndex];
}