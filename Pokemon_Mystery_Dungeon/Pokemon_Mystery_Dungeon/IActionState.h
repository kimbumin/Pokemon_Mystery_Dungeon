#pragma once
// clang-format off
#include "config.h"
// clang-format on

class PokemonBase;
class IActionState
{
private:
public:
    virtual void Enter(PokemonBase* owner) = 0;
    virtual void Update(PokemonBase* owner) = 0;
    virtual void Exit(PokemonBase* owner) = 0;
    virtual bool IsFinished() = 0;
    virtual bool CanOverride() = 0;

    virtual ~IActionState() {};
};
