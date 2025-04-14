#pragma once
#include "config.h"

class PokemonBase;
class IAnimState
{
private:

public:
	virtual void Enter(PokemonBase* outer) = 0;
	virtual void Update(PokemonBase* outer) = 0;
	virtual void Exit(PokemonBase* outer) = 0;
	virtual bool IsFinished() = 0;

	virtual ~IAnimState() {};
};

