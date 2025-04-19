#include "HurtState.h"
#include "PokemonBase.h"

void HurtState::Enter(PokemonBase* owner)
{
	isFinished = false;
}

void HurtState::Update(PokemonBase* owner)
{ 
	if (owner->GetCurrentPokemonData().hp >= 0)
	{

	}
}

void HurtState::Exit(PokemonBase* owner)
{
}

bool HurtState::IsFinished()
{
	return isFinished;
}

bool HurtState::CanOverride()
{
	return false;
}
