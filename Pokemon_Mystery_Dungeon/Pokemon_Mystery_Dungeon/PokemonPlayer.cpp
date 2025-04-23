#include "PokemonPlayer.h"

#include <cmath>

#include "Camera.h"
#include "ISkill.h"
#include "SkillManager.h"

HRESULT PokemonPlayer::Init()
{
    PokemonBase::Init();
    exp = pow(level, 3);
    expToLevelUp = pow((level + 1), 3);
    learnedSkill[0] =
        SkillManager::GetInstance()->CreateSkill("BodySlam");  // Check
    learnedSkill[1] = SkillManager::GetInstance()->CreateSkill("FireBlast");
    learnedSkill[2] = SkillManager::GetInstance()->CreateSkill("DoubleEdge");
    learnedSkill[3] = SkillManager::GetInstance()->CreateSkill("Ember");
    UpdateRect();
    return S_OK;
}

void PokemonPlayer::Release()
{
}

void PokemonPlayer::Update()
{
    if (isInSquare)
    {
        SavePrevPos();
        SquareModeMove();
        UpdateRect();
        PokemonBase::Update();

    }
    else
    {
        PokemonBase::Update();
    }
    Camera::GetInstance()->SetCameraPos(
        POINT{static_cast<int>(pos.x), static_cast<int>(pos.y)});
}

void PokemonPlayer::SquareModeMove()
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
    {
        direction = Direction::WEST;
        pos.x -= .1f;
    }
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
    {
        direction = Direction::EAST;
        pos.x += .1f;
    }
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
    {
        direction = Direction::NORTH;
        pos.y -= .1f;
    }
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
    {
        direction = Direction::SOUTH;
        pos.y += .1f;
    }
}

void PokemonPlayer::UpdateRect()
{
    rect.left = pos.x - size.cx / 2;
    rect.top = pos.y - size.cy / 2;
    rect.right = pos.x + size.cx / 2;
    rect.bottom = pos.y + size.cy / 2;
}

bool PokemonPlayer::CanPickUpItem() const
{
    return false;
}

void PokemonPlayer::PickUpItem(Item* item)
{
}

void PokemonPlayer::AddItemToBag(Item* item)
{
}

void PokemonPlayer::UseItem(Item* item)
{
}

void PokemonPlayer::GainExp(int amount)
{
    exp += amount;
    if (exp > expToLevelUp)
    {
        LevelUp();
    }
}

void PokemonPlayer::LevelUp()
{
    // 진화 체크
    ++level;
    expToLevelUp = pow((level + 1), 3);
    CalStatus();
}
