#include "SwingSkill.h"

#include "BattleSystem.h"
#include "Image.h"
#include "PokemonBase.h"

SwingSkill::SwingSkill(const SkillData& skillData)
{
    data = skillData;
    direction = 0;
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = nullptr;
}

HRESULT SwingSkill::Init()
{
    return S_OK;
}

void SwingSkill::Release()
{
}

void SwingSkill::Update()
{
    if (isActive)
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

        if (elapsedTime >= 1.f)
        {
            isActive = false;
            elapsedTime = 0;
        }
    }
}

void SwingSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRender(hdc, pos.x, pos.y, frameX, 0);
    }
}

void SwingSkill::Use(PokemonBase* owner)
{
    direction = static_cast<int>(owner->GetDirection());
    pos = owner->GetPos();
    auto dirIndex = static_cast<size_t>(direction);

    pos.x += directionOffsets[dirIndex].first * 24;
    pos.y += directionOffsets[dirIndex].second * 24;

    isActive = true;

    PokemonBase* target = BattleSystem::GetInstance()->GetTargetInFront(owner);
    if (target)
    {
        int damage =
            BattleSystem::GetInstance()->CalculateDamage(owner, target, this);
        target->TakeDamage(damage);
    }
}

shared_ptr<ISkill> SwingSkill::Clone()
{
    return make_shared<SwingSkill>(*this);
}
