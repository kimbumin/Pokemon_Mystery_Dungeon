#pragma once
#include "config.h"

class PokemonBase;
class PokemonMovement
{
private:
	PokemonBase* outer;
    float moveXDistance = TILE_X;
    float moveYDistance = TILE_Y;
protected:

public:

    void Move(Direction direction);
    void Look(Direction direction);
    void Update();


    // Getter

    // Setter
    void SetOwner(PokemonBase* outer) { this->outer = outer; }


};