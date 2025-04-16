#pragma once
#include "GameObject.h"

class PokemonAnimator;
class IAnimState;
class PokemonBase : public GameObject
{
private:

protected:
    const PokemonData* baseStatus;
    PokemonData currentStatus;
    PokemonAnimator* animator;

    IAnimState* currentAnimState;

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

    void SetAnimState(IAnimState* newState);

    // Getter
    inline PokemonData GetCurrentPokemonData() { return currentStatus; }
    inline PokemonAnimator* GetAnimator() { return animator; }
    inline Direction GetDirection() { return direction; }
    inline FPOINT GetPos() { return pos; }
    inline int GetLevel() { return level; }
    inline bool GetIsAlive() { return isAlive; }

    //Setter
    inline void SetStatus(PokemonData* baseStatus) { this->baseStatus = baseStatus; }
    inline void SetPos(FPOINT pos) { this->pos = pos; }
    inline void SetLevel(int level) { this->level = level; }
    inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
    
    PokemonBase() {};
    virtual ~PokemonBase() {};
};