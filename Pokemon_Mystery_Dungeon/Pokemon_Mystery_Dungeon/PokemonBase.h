#pragma once
#include "GameObject.h"
#include "ISkill.h"

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

class Map;
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

    FPOINT pos = {500, 300};
    Map* dungeonMap;
    int level;
    int currentHp;
    bool isAlive;
    bool isTurnComplete;
    Direction direction = Direction::SOUTH;

    // 배운 스킬 리스트
    // UI에서 SkillIndex를 TurnManager로 전달 or *** TurnManager에서
    // GetSelectedSkillIndex로, TurnManager에서 GetSkillList로 Seleted
    vector<shared_ptr<ISkill>> learnedSkill;

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void CalStatus();
    virtual int CalStat(int value);

    virtual void TakeDamage(int damage);
    // virtual void StartTurn() = 0;

    void SetAnimState(IAnimState* newState);
    void SetActionState(IActionState* newState);

    virtual void ExecuteTurn();
    Direction CalculateDirection(FPOINT& targetPos);

    // Getter
    inline PokemonData GetCurrentPokemonData()
    {
        return currentStatus;
    }
    inline PokemonAnimator* GetAnimator()
    {
        return animator;
    }
    inline IAnimState* GetCurrentAnimState()
    {
        return currentAnimState;
    }
    inline IActionState* GetCurrentActionState()
    {
        return currentActionState;
    }
    inline Direction GetDirection()
    {
        return direction;
    }
    inline FPOINT GetPos()
    {
        return pos;
    }
    inline Map* GetMap()
    {
        return dungeonMap;
    }
    inline int GetLevel()
    {
        return level;
    }
    inline bool GetIsAlive()
    {
        return isAlive;
    }
    inline int GetCurrentHp() const
    {
        return currentHp;
    }
    shared_ptr<ISkill> GetSkill(int index)
    {
        return learnedSkill[index];
    }

    // Setter
    inline void SetStatus(const PokemonData* baseStatus)
    {
        this->baseStatus = baseStatus;
    }
    inline void SetHp(int hp)
    {
        this->currentHp = hp;
    }
    inline void SetDirection(Direction direction)
    {
        this->direction = direction;
    }
    inline void SetPos(FPOINT pos)
    {
        this->pos = pos;
    }
    inline void SetMap(Map* newMap)
    {
        dungeonMap = newMap;
    }
    inline void SetLevel(int level)
    {
        this->level = level;
    }
    inline void SetIsAlive(bool isAlive)
    {
        this->isAlive = isAlive;
    }
    inline void SetSkill(int index, shared_ptr<ISkill> skill)
    {
        this->learnedSkill[index] = skill;
    }
    void SetAnimator();

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
    void ExecuteAttackAction(shared_ptr<ISkill> skill);
    void ExecuteHurtAction();

    // Rapper Skill Render
    void SkillRender(HDC hdc, ISkill* skill);

    // virtual void ExecuteTurn() = 0;

    PokemonBase() {};
    virtual ~PokemonBase() {};
};