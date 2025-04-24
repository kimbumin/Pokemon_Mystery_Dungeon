#include "PokemonPlayer.h"

#include <cmath>

#include "Camera.h"
#include "CommonFunction.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "ISkill.h"
#include "PokemonAnimator.h"
#include "PokemonDataLoader.h"
#include "PokemonEvolutionDataLoader.h"
#include "SkillManager.h"
#include "PokemonImageLoader.h"
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
    PokemonBase::Update();
    if (isInSquare)
    {
        SavePrevPos();
        SquareModeMove();
        UpdateRect();
    }
    else
    {
        // Test
        if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
        {
            GainExp(5000);
        }
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_OEM_PLUS))
        Camera::GetInstance()->ZoomIn();
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_OEM_MINUS))
        Camera::GetInstance()->ZoomOut();

    Camera::GetInstance()->SetCameraPos(
        POINT{ static_cast<int>(pos.x), static_cast<int>(pos.y) });
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
    DialogueManager::GetInstance()->ShowLine(DialogueTemplate::GainedExp,
                                             {{L"exp", ToWString(amount)}});
    exp += amount;
    if (exp > expToLevelUp)
    {
        LevelUp();
    }
}

void PokemonPlayer::LevelUp()
{
    // check ·Î±× Ãâ·Â
    // Print Log
    PokemonData prevStatus = currentStatus;

    ++level;
    expToLevelUp = pow((level + 1), 3);
    TryEvolve();
    CalStatus();
}

void PokemonPlayer::TryEvolve()
{
    int currentId = baseStatus->idNumber;
    EvolutionData* evolutionData =
        PokemonEvolutionDataLoader::GetInstance()->GetData(currentId);
    if (evolutionData && level >= evolutionData->requiredLevel)
    {
        EvolveTo(evolutionData->evolvedPokemonId);
    }
}

void PokemonPlayer::EvolveTo(int newPokemonId)
{
    PokemonImageLoader::GetInstance()->LoadPokemonAnim(newPokemonId);
    baseStatus = PokemonDataLoader::GetInstance()->GetData(newPokemonId);
    if (baseStatus == nullptr)
    {
        return;
    }
    CalStatus();

    if (animator)
    {
        animator->Release();
        delete animator;
    }
    animator = new PokemonAnimator();
    SetAnimator();
    PlayIdleAnim();
    // check ·Î±× Ãâ·Â or ÁøÈ­ ¿¬Ãâ
    // Print Log or Evolution Effect
}

void PokemonPlayer::PrintLevelUpSummaryDialogue(const PokemonData& prevStatus,
                                                const PokemonData& newStatus)
{
    struct StatChange
    {
        wstring name;
        int prevValue;
        int newValue;
    };

    std::vector<StatChange> changes = {
        {L"HP", prevStatus.hp, newStatus.hp},
        {L"Attack", prevStatus.atk, newStatus.atk},
        {L"Defense", prevStatus.def, newStatus.def},
        {L"Sp. Atk", prevStatus.spAtk, newStatus.spAtk},
        {L"Sp. Def", prevStatus.spDef, newStatus.spDef},
        {L"Speed", prevStatus.speed, newStatus.speed}};

    std::wstring statChanges;
    bool first = true;

    for (const auto& change : changes)
    {
        int diff = change.newValue - change.prevValue;
        if (diff > 0)
        {
            if (!first)
            {
                statChanges += L", ";
            }
            statChanges += change.name + L" +" + ToWString(diff);
            first = false;
        }
    }

    // Check DialogueManager¸¦ ÅëÇØ Ãâ·Â
    // DialogueManager::GetInstance()->ShowLine(DialogueTemplate::LevelUpSummary,
    // {{L"statChanges", statChanges}});
}