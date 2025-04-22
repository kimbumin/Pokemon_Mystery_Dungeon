#include "PokemonEnemy.h"
#include "PokemonBase.h"

#include "IdleAnimState.h"
#include "AttackAnimState.h"
#include "WalkAnimState.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "HurtAnimState.h"

#include "MoveActionState.h"
#include "IdleActionState.h"
#include "AttackActionState.h"
#include "HurtActionState.h"

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
    ExecuteMoveAction(); // Test
}
