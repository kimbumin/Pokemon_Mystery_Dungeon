#pragma once
#include "GameObject.h"

class Image;
class PokemonBase : public GameObject
{
private:

protected:
    const PokemonData* baseStatus;
    PokemonData currentStatus;
    Image* image;
    FPOINT pos = { 0,0 };
    int level;
    int currentHp;
    bool isAlive;

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void CalStatus();
    virtual int CalStat(int value);
    PokemonBase() {};
    virtual ~PokemonBase() {};
};