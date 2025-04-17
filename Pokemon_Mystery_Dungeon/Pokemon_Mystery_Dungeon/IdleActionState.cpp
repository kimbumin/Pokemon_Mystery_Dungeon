#include "IdleActionState.h"

void IdleActionState::Enter(PokemonBase* owner)
{
	isFinished = false;
}

void IdleActionState::Update(PokemonBase* owner)
{
}

void IdleActionState::Exit(PokemonBase* owner)
{
}

bool IdleActionState::IsFinished()
{
	return isFinished;
}

bool IdleActionState::CanOverride()
{
	return true;
}

IdleActionState::IdleActionState()
{
	isFinished = false;
}
