#pragma once
#include "IActionState.h"

class HurtState : public IActionState
{
private:
	bool isFinished;
public:
	virtual void Enter(PokemonBase* owner) = 0;
	virtual void Update(PokemonBase* owner) = 0;
	virtual void Exit(PokemonBase* owner) = 0;
	virtual bool IsFinished() = 0;
	virtual bool CanOverride() = 0;

	HurtState() {};
	virtual ~HurtState() {};
};

