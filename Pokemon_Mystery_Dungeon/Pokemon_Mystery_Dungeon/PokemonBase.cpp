#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "Image.h"
#include "PokemonAnimator.h"

#include "IdleAnimState.h"
#include "AttackAnimState.h"
#include "WalkAnimState.h"
#include "RotateAnimState.h"
#include "SwingAnimState.h"
#include "HurtAnimState.h"

#include "MoveActionState.h"
#include "IdleActionState.h"
#include "AttackActionState.h"
#include "HurtActionState.h"

// Skill
// UseItem

HRESULT PokemonBase::Init()
{
    // isAlive = false;
    // baseStatus = PokemonDataLoader::GetInstance()->GetData(0);
    currentStatus = *baseStatus;
    // level = 0;
    CalStatus();
    currentHp = currentStatus.hp;

    animator = new PokemonAnimator();

    walkAnim = new WalkAnimState;
    idleAnim = new IdleAnimState;
    attackAnim = new AttackAnimState;
    hurtAnim = new HurtAnimState;
    swingAnim = new SwingAnimState;
    rotateAnim = new RotateAnimState;

    moveAction = new MoveActionState;
    idleAction = new IdleActionState;
    attackAction = new AttackActionState;
    hurtAction = new HurtActionState;

    currentAnimState = nullptr;
    currentActionState = nullptr;

    SetAnimState(idleAnim);
    SetActionState(idleAction);

    SetAnimator();
    return S_OK;
}

void PokemonBase::Release()
{
    if (animator)
    {
        animator->Release();
        delete animator;
        animator = nullptr;
    }
    // 이거 지우는 거 매크로고려
    if (walkAnim)
    {
        delete walkAnim;
        walkAnim = nullptr;
    }
    if (idleAnim)
    {
        delete idleAnim;
        idleAnim = nullptr;
    }   
    if (attackAnim)
    {
        delete attackAnim;
        attackAnim = nullptr;
    }   
    if (hurtAnim)
    {
        delete hurtAnim;
        hurtAnim = nullptr;
    }   
    if (swingAnim)
    {
        delete swingAnim;
        swingAnim = nullptr;
    }   
    if (rotateAnim)
    {
        delete rotateAnim;
        rotateAnim = nullptr;
    }
    if (moveAction)
    {
        delete moveAction;
        moveAction = nullptr;
    }
    if (idleAction)
    {
        delete idleAction;
        idleAction = nullptr;
    }
    if (attackAction)
    {
        delete attackAction;
        attackAction = nullptr;
    }
    if (hurtAction)
    {
        delete hurtAction;
        hurtAction = nullptr;
    }
}

void PokemonBase::Update()
{
   /* if (currentActionState->CanOverride())
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
        {
            direction = Direction::NORTH;
            SetActionState(moveAction);
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
        {
            direction = Direction::WEST;
            SetActionState(moveAction);
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
        {
            direction = Direction::SOUTH;
            SetActionState(moveAction);
        }
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
        {
            direction = Direction::EAST;
            SetActionState(moveAction);
        }
    }*/
    if (currentAnimState)
    {
        currentAnimState->Update(this);
    }
    if (currentActionState && currentActionState->IsFinished())
    {
        SetActionState(idleAction);
    }
    if (currentActionState)
    {
        currentActionState->Update(this);
    }

}

void PokemonBase::Render(HDC hdc)
{
    animator->Render(hdc, pos.x, pos.y);
}

void PokemonBase::CalStatus()
{
    currentStatus.hp = CalStat(baseStatus->hp) + 10/*보정값*/;
    currentStatus.atk = CalStat(baseStatus->atk) + 5/*보정값*/;
    currentStatus.def = CalStat(baseStatus->def) + 5/*보정값*/;
    currentStatus.spAtk = CalStat(baseStatus->spAtk) + 5/*보정값*/;
    currentStatus.spDef = CalStat(baseStatus->spDef) + 5/*보정값*/;
    currentStatus.speed = CalStat(baseStatus->speed) + 5/*보정값*/;
}

int PokemonBase::CalStat(int value)
{
    return (value + IV + EV + 100) * level / 100;
}

void PokemonBase::TakeDamage()
{
    // 데미지 입는 것을 입는 관점에서 or 주는 관점에서
    // 입히는 데미지를 전투 시스템에서 전달하고 전투시스템에서 계산 때리고 그 결과를 이걸로 적용하는 구조
}

void PokemonBase::SetAnimState(IAnimState* newState)
{
    if (currentAnimState && !currentAnimState->CanOverride())
    {
        return;
    }
    if (currentAnimState)
    {
       currentAnimState->Exit(this);
    }
    currentAnimState = newState;
    if (currentAnimState)
    {
        currentAnimState->Enter(this);
    }
}

void PokemonBase::SetActionState(IActionState* newState)
{
    if (currentActionState && !currentActionState->CanOverride())
    {
        return;
    }

    if (currentActionState)
    {
        currentActionState->Exit(this);
    }
    currentActionState = newState;
    if (currentActionState)
    {
        currentActionState->Enter(this);
    }
}

void PokemonBase::SetAnimator()
{
    string idStr = PokemonImageLoader::GetInstance()->PokemonIdToString(baseStatus->idNumber);
    for (auto type = animTypes.begin(); type != animTypes.end(); ++type)
    {
        string key = idStr + *type;
        Image* image = ImageManager::GetInstance()->FindImage(key);
        if (image)
        {
            int frameX = image->GetMaxFrameX();
            int frameY = image->GetMaxFrameY();
            float frameTime = 1.f / frameX; //  Check: 재생 속도 하드코딩 개선 사항 (CSV에 있는 데이터로 매 프레임마다 재생속도도 다르게 할 수 있다)
            animator->AddAnimation(*type, image, frameX, frameY, frameTime, *type == "Idle");
            // 반복되는 애니메이션은 Idle만 있어서
        }
    }
}

void PokemonBase::PlayWalkAnim()
{ 
    SetAnimState(walkAnim); 
}
void PokemonBase::PlayIdleAnim() 
{ 
    SetAnimState(idleAnim); 
}
void PokemonBase::PlayAttackAnim() 
{ 
    SetAnimState(attackAnim); 
}
void PokemonBase::PlayHurtAnim() 
{ 
    SetAnimState(hurtAnim); 
}
void PokemonBase::PlaySwingAnim() 
{ 
    SetAnimState(swingAnim); 
}
void PokemonBase::PlayRotateAnim() 
{ 
    SetAnimState(rotateAnim); 
}

void PokemonBase::ExecuteMoveAction()
{
    SetActionState(moveAction);
}

void PokemonBase::ExecuteIdleAction()
{
    SetActionState(idleAction);
}

void PokemonBase::ExecuteAttackAction(ISkill* skill)
{
    attackAction->SelectSkill(skill);
    SetActionState(attackAction);
}

void PokemonBase::ExecuteHurtAction()
{
    SetActionState(hurtAction);
}