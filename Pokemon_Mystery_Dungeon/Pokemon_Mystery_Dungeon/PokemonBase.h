#pragma once
#include "GameObject.h"


class PokemonAnimator;
class IAnimState;
class IActionState;

class WalkAnimState;
class IdleAnimState;
class AttackAnimState;
class HurtAnimState;
class SwingAnimState;
class RotateAnimState;

class MoveActionState;
class IdleActionState;
class AttackActionState;
class HurtActionState;

class ISkill;
class PokemonBase : public GameObject
{
private:

protected:

    const PokemonData* baseStatus;
    PokemonData currentStatus;
    PokemonAnimator* animator;

    IAnimState* currentAnimState;
    IActionState* currentActionState;

    // AnimState Pooling
    WalkAnimState* walkAnim;
    IdleAnimState* idleAnim;
    AttackAnimState* attackAnim;
    HurtAnimState* hurtAnim;
    SwingAnimState* swingAnim;
    RotateAnimState* rotateAnim;

    // ActionState Pooling
    MoveActionState* moveAction;
    IdleActionState* idleAction;
    AttackActionState* attackAction;
    HurtActionState* hurtAction;

    FPOINT pos = { 240 ,240 };
    int level;
    int currentHp;
    bool isAlive;
    Direction direction = Direction::SOUTH;

    // 배운 스킬 리스트
    // UI에서 SkillIndex를 TurnManager로 전달 or *** TurnManager에서 GetSelectedSkillIndex로, 
    // TurnManager에서 GetSkillList로 Seleted 

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void CalStatus();
    virtual int CalStat(int value);

    virtual void TakeDamage();
    //virtual void StartTurn() = 0;

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

    // Rapper Anim Function
    void PlayWalkAnim();
    void PlayIdleAnim();
    void PlayAttackAnim();
    void PlayHurtAnim();
    void PlaySwingAnim();
    void PlayRotateAnim();

    // Rapper Action Function
    void ExecuteMoveAction();
    void ExecuteIdleAction();
    void ExecuteAttackAction(ISkill* skill);
    void ExecuteHurtAction();

    PokemonBase() {};
    virtual ~PokemonBase() {};
};