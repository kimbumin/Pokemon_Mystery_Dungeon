#pragma once
#include "PokemonBase.h"

class Map;
class PokemonEnemy : public PokemonBase
{
private:
protected:
public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void ExecuteTurn() override;
    vector<FPOINT> AStarPathfinding(int startX, int startY, int goalX,
                                    int goalY);

    float Heuristic(int x1, int y1, int x2, int y2);

    vector<FPOINT> ReconstructPath(
        map<pair<int, int>, pair<int, int>>& cameFrom, int goalX, int goalY,
        int startX, int startY);

        Direction GetRandomWalkableDirection();

    PokemonEnemy() {};
    virtual ~PokemonEnemy() {};
};
