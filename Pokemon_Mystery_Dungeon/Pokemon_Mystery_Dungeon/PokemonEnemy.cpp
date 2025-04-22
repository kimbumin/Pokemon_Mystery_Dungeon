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
#include "MoveActionState.h"
#include "PlayerManager.h"
#include "PokemonBase.h"
#include "PokemonPlayer.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "WalkAnimState.h"
#include "Map.h"

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

    int dist = abs(myX - playerX) + abs(myY - playerY);

    Direction dirToPlayer = CalculateDirection(playerPos);
    this->SetDirection(dirToPlayer);
    if (dist <= 1)
    {
        ExecuteAttackAction(nullptr);  // 임시로 nullptr, 나중에 Skill1 연결
    }
    else if (dist <= 3)
    {
        auto path = AStarPathfinding(myX, myY, playerX, playerY);
        if (!path.empty())
        {
            FPOINT nextPos = path[0];
            Direction moveDir = CalculateDirection(nextPos);
            this->SetDirection(moveDir);
            ExecuteMoveAction();
        }
    }
    else
    {
        Direction randomDir = GetRandomWalkableDirection();
        this->SetDirection(randomDir);
        ExecuteMoveAction();
    }
}

vector<FPOINT> PokemonEnemy::AStarPathfinding(int startX, int startY, int goalX, int goalY)
{
    priority_queue<pair<float, pair<int, int>>, vector<pair<float, pair<int, int>>>, greater<>> openSet;
    set<pair<int, int>> closedSet;
    map<pair<int, int>, pair<int, int>> cameFrom;
    map<pair<int, int>, float> gScore;

    pair<int, int> start = { startX, startY };
    pair<int, int> goal = { goalX, goalY };

    gScore[start] = 0.0f;
    openSet.push({ Heuristic(startX, startY, goalX, goalY), start });

    while (!openSet.empty())
    {
        pair<int, int> current = openSet.top().second;
        openSet.pop();

        if (current == goal)
        {
            return ReconstructPath(cameFrom, current.first, current.second);
        }

        closedSet.insert(current);

        for (int i = 0; i < 8; ++i)
        {
            int nextX = current.first + directionOffsets[i].first;
            int nextY = current.second + directionOffsets[i].second;
            pair<int, int> neighbor = { nextX, nextY };

            if (learnedMap != nullptr)
            {
                if (!learnedMap->IsPathOrFloor(nextX, nextY) || closedSet.count(neighbor))
                {
                    continue;
                }
            }
           

            float tentativeG = gScore[current] + ((i % 2 == 0) ? 1.0f : 1.414f);

            if (!gScore.count(neighbor) || tentativeG < gScore[neighbor])
            {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeG;
                float fScore = tentativeG + Heuristic(nextX, nextY, goalX, goalY);
                openSet.push({ fScore, neighbor });
            }
        }
    }

    return {}; // 경로 없음
}

float PokemonEnemy::Heuristic(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

vector<FPOINT> PokemonEnemy::ReconstructPath(map<pair<int, int>, pair<int, int>>& cameFrom, int goalX, int goalY)
{
    vector<FPOINT> path;
    pair<int, int> current = { goalX, goalY };

    while (cameFrom.find(current) != cameFrom.end())
    {
        FPOINT worldPos = { current.first * TILE_SIZE * 1.0f, current.second * TILE_SIZE * 1.0f };
        path.insert(path.begin(), worldPos);
        current = cameFrom[current];
    }

    return path;
}

Direction PokemonEnemy::GetRandomWalkableDirection()
{
    vector<Direction> possibleDirs;

    for (int i = 0; i < 8; ++i)
    {
        int nextX = static_cast<int>(pos.x / TILE_SIZE) + directionOffsets[i].first;
        int nextY = static_cast<int>(pos.y / TILE_SIZE) + directionOffsets[i].second;

        if (learnedMap != nullptr)
        {
            if (learnedMap->IsPathOrFloor(nextX, nextY))
            {
                possibleDirs.push_back(static_cast<Direction>(i));
            }
        }
        
    }

    if (possibleDirs.empty())
    {
        return GetDirection(); // 이동 못하면 현재 방향 유지
    }

    int randomIndex = rand() % possibleDirs.size();
    return possibleDirs[randomIndex];
}