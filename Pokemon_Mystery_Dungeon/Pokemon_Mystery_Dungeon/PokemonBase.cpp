#include "PokemonBase.h"

#include "AttackActionState.h"
#include "AttackAnimState.h"
#include "HurtActionState.h"
#include "HurtAnimState.h"
#include "IdleActionState.h"
#include "IdleAnimState.h"
#include "Image.h"
#include "MoveActionState.h"
#include "PokemonAnimator.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "RotateAnimState.h"
#include "SkillManager.h"
#include "SwingAnimState.h"
#include "WalkAnimState.h"

// Skill
// UseItem

HRESULT PokemonBase::Init()
{
    isAlive = true;
    learnedSkill.resize(4, nullptr);
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
    for (size_t i = 0; i < learnedSkill.size(); ++i)
    {
        if (learnedSkill[i] && learnedSkill[i]->IsActive())
        {
            learnedSkill[i]->Update();
        }
    }
}

void PokemonBase::Render(HDC hdc)
{
    animator->Render(hdc, pos.x, pos.y);

    for (size_t i = 0; i < learnedSkill.size(); ++i)
    {
        if (learnedSkill[i] && learnedSkill[i]->IsActive())
        {
            learnedSkill[i]->Render(hdc);
        }
    }
}

void PokemonBase::CalStatus()
{
    currentStatus.hp = CalStat(baseStatus->hp) + 10;
    currentStatus.atk = CalStat(baseStatus->atk) + 5;
    currentStatus.def = CalStat(baseStatus->def) + 5;
    currentStatus.spAtk = CalStat(baseStatus->spAtk) + 5;
    currentStatus.spDef = CalStat(baseStatus->spDef) + 5;
    currentStatus.speed = CalStat(baseStatus->speed) + 5;
}

int PokemonBase::CalStat(int value)
{
    return (value + IV + EV + 100) * level / 100;
}

void PokemonBase::TakeDamage()
{
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

void PokemonBase::ExecuteTurn()
{
    // 동료와 Enemy 확장을 위해 남겨줌
}

Direction PokemonBase::CalculateDirection(FPOINT& targetPos)
{
    int dx = static_cast<int>(targetPos.x - pos.x);
    int dy = static_cast<int>(targetPos.y - pos.y);

    dx /= TILE_SIZE;
    dy /= TILE_SIZE;

    if (dx == 0 && dy > 0)
        return Direction::SOUTH;
    if (dx > 0 && dy > 0)
        return Direction::SOUTHEAST;
    if (dx > 0 && dy == 0)
        return Direction::EAST;
    if (dx > 0 && dy < 0)
        return Direction::NORTHEAST;
    if (dx == 0 && dy < 0)
        return Direction::NORTH;
    if (dx < 0 && dy < 0)
        return Direction::NORTHWEST;
    if (dx < 0 && dy == 0)
        return Direction::WEST;
    if (dx < 0 && dy > 0)
        return Direction::SOUTHWEST;

    return Direction::SOUTH;
}

void PokemonBase::SetAnimator()
{
    string idStr = PokemonImageLoader::GetInstance()->PokemonIdToString(
        baseStatus->idNumber);
    for (auto type = animTypes.begin(); type != animTypes.end(); ++type)
    {
        string key = idStr + *type;
        Image* image = ImageManager::GetInstance()->FindImage(key);
        if (image)
        {
            int frameX = image->GetMaxFrameX();
            int frameY = image->GetMaxFrameY();
            float frameTime;
            if (*type == "Walk")
            {
                frameTime = 0.2f / frameX;
            }
            else if (*type == "Idle")
            {
                frameTime = 1.f / frameX;
            }
            else
            {
                frameTime = 0.5f / frameX;
                //  Check: 재생 속도 하드코딩 개선 사항 (CSV에
                //  있는 데이터로 매 프레임마다 재생속도도 다르게
                //  할 수는 있다)
                // Improvements to hard-coding playback speed (with data in CSV,
                // playback speed can be different for each frame)
            }
            animator->AddAnimation(*type, image, frameX, frameY, frameTime,
                                   *type == "Idle");
            // 占쌥븝옙占실댐옙 占쌍니몌옙占싱쇽옙占쏙옙 Idle占쏙옙 占쌍어서
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

void PokemonBase::ExecuteAttackAction(shared_ptr<ISkill> skill)
{
    attackAction->SelectSkill(skill);
    SetActionState(attackAction);
}

void PokemonBase::ExecuteHurtAction()
{
    SetActionState(hurtAction);
}