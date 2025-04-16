#pragma once
#include "IAnimState.h"

class SwingAnimState : public IAnimState
{
private:
	bool finished;
public:
	virtual void Enter(PokemonBase* outer) override;
	virtual void Update(PokemonBase* outer) override;
	virtual void Exit(PokemonBase* outer) override;
	virtual bool IsFinished() override;
	virtual bool CanOverride() override;

	SwingAnimState();
	virtual ~SwingAnimState() {};
};

