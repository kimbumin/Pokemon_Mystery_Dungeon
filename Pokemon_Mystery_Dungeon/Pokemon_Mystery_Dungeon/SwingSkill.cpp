#include "SwingSkill.h"

#include "Image.h"
#include "PokemonBase.h"

SwingSkill::SwingSkill(const SkillData& skillData)
{
    data = skillData;
}

HRESULT SwingSkill::Init()
{
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = ImageManager::GetInstance()->AddImage(
        "Swing", TEXT("Image/SkillImage/Swing.bmp"), 190, 19, 10, 1, true,
        RGB(255, 0, 255));

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

        if (elapsedTime >= 0.02f)
        {
            frameCount++;
            elapsedTime = 0.0f;
        }

        if (frameCount >= image->GetMaxFrameX())
        {
            isActive = false;
            frameCount = 0;
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
}

shared_ptr<ISkill> SwingSkill::Clone()
{
    return make_shared<SwingSkill>(*this);
}
