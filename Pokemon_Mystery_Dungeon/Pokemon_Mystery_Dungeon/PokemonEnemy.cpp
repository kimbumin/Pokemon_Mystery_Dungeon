#include "PokemonEnemy.h"

#include "AttackActionState.h"
#include "AttackAnimState.h"
#include "HurtActionState.h"
#include "HurtAnimState.h"
#include "IdleActionState.h"
#include "IdleAnimState.h"
#include "MoveActionState.h"
#include "PokemonBase.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
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
    ExecuteMoveAction();  // Test
}
