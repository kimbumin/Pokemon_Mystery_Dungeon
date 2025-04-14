#pragma once
#include "GameObject.h"

class PokemonAnimator;
class PokemonBase : public GameObject
{
private:

protected:
    const PokemonData* baseStatus;
    PokemonData currentStatus;
    PokemonAnimator* animator;

    FPOINT pos = { 100,100 };
    int level;
    int currentHp;
    bool isAlive;
    Direction direction = Direction::SOUTH;


public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void CalStatus();
    virtual int CalStat(int value);

    inline PokemonData GetCurrentPokemonData() { return currentStatus; }

    PokemonBase() {};
    virtual ~PokemonBase() {};
};