#include "AttackSkill.h"

#include "PokemonBase.h"

AttackSkill::AttackSkill(const SkillData& skillData)
{
    data = skillData;
}

HRESULT AttackSkill::Init()
{
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = nullptr;
    return S_OK;
}

void AttackSkill::Release()
{
}

void AttackSkill::Update()
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

void AttackSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRender(hdc, pos.x, pos.y, frameX, 0);
    }
}

void AttackSkill::Use(PokemonBase* owner)
{
    direction = static_cast<int>(owner->GetDirection());
    pos = owner->GetPos();
    auto dirIndex = static_cast<size_t>(direction);

    pos.x += directionOffsets[dirIndex].first * 24;
    pos.y += directionOffsets[dirIndex].second * 24;

    isActive = true;
}

shared_ptr<ISkill> AttackSkill::Clone()
{
    return make_shared<AttackSkill>(*this);
}
