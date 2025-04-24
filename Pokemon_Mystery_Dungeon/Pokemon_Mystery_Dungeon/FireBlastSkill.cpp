#include "FireBlastSkill.h"

#include "PokemonBase.h"
#include "Camera.h"
FireBlastSkill::FireBlastSkill(const SkillData& skillData)
{
    data = skillData;
}

HRESULT FireBlastSkill::Init()
{
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = ImageManager::GetInstance()->AddImage(
        "FireBlast", TEXT("Image/SkillImage/FireBlast.bmp"), 1856 / 2, 61 / 2, 29,
        1, true, RGB(255, 0, 255));

    return S_OK;
}

void FireBlastSkill::Release()
{
}

void FireBlastSkill::Update()
{
    if (isActive)
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();  // 누적

        if (elapsedTime >= (1.f) / image->GetMaxFrameX())  // 0.2초마다 실행
        {
            frameCount++;
            elapsedTime = 0.0f;  // 다시 0으로 초기화
        }

        if (frameCount >= image->GetMaxFrameX())
        {
            isActive = false;
            frameCount = 0;
        }
    }
}

void FireBlastSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRenderWithCamera(hdc, pos.x, pos.y, frameX, 0, 0, true);
    }
}

void FireBlastSkill::Use(PokemonBase* owner)
{
    direction = static_cast<int>(owner->GetDirection());
    pos = owner->GetPos();
    auto dirIndex = static_cast<size_t>(direction);

    // 여기 수정
    pos.x += directionOffsets[dirIndex].first * 24;
    pos.y += directionOffsets[dirIndex].second * 24;
    Camera::GetInstance()->Shake(0.1f, 5);
    isActive = true;
}

shared_ptr<ISkill> FireBlastSkill::Clone()
{
    return make_shared<FireBlastSkill>(*this);  // 스킬을 복제하여 반환
}
