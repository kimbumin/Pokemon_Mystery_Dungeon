#pragma once
#include "GameObject.h"

#include "IdleAnimState.h"
#include "AttackAnimState.h"
#include "WalkAnimState.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "HurtAnimState.h"

class PokemonAnimator;
class IAnimState;
class IActionState;
class PokemonBase : public GameObject
{
private:

protected:

    const PokemonData* baseStatus;
    PokemonData currentStatus;
    PokemonAnimator* animator;

    IAnimState* currentAnimState;
    IActionState* currentActionState;

    WalkAnimState walkAnim;
    IdleAnimState idleAnim;
    AttackAnimState attackAnim;
    HurtAnimState hurtAnim;
    SwingAnimState swingAnim;
    RotateAnimState rotateAnim;

    FPOINT pos = { 240 ,240 };
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
    void SetActionState(IActionState* newState);

    // Getter
    inline PokemonData GetCurrentPokemonData() { return currentStatus; }
    inline PokemonAnimator* GetAnimator() { return animator; }
    inline Direction GetDirection() { return direction; }
    inline FPOINT GetPos() { return pos; }
    inline int GetLevel() { return level; }
    inline bool GetIsAlive() { return isAlive; }

    //Setter
    inline void SetStatus(PokemonData baseStatus) { this->baseStatus = &baseStatus; }
    inline void SetDirection(Direction direction) { this->direction = direction; }
    inline void SetPos(FPOINT pos) { this->pos = pos; }
    inline void SetLevel(int level) { this->level = level; }
    inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }

    // Rapper Function
    void PlayWalkAnim();
    void PlayIdleAnim();
    void PlayAttackAnim();
    void PlayHurtAnim();
    void PlaySwingAnim();
    void PlayRotateAnim();

    PokemonBase() {};
    virtual ~PokemonBase() {};
};