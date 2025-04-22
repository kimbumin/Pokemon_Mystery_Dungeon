#include "EmberSkill.h"

void EmberSkill::Init()
{
    pos.x = 0;
    pos.y = 0;
    name = "Ember";
    stats.power = 40;
    stats.accuracy = 100;
    stats.maxPP = 25;

    image = ImageManager::GetInstance()->AddImage(
        "Ember", TEXT("Image/.bmp"), 1, 1, 1, 1, true, RGB(255, 0, 255));
}

void EmberSkill::Release()
{
}

void EmberSkill::Update()
{
}

void EmberSkill::Render(HDC hdc)
{
    image = ImageManager::GetInstance()->FindImage("Ember");
    if (image)
    {
        image->FrameRender(hdc, pos.x, pos.y, 0, 0);
    }
}

void EmberSkill::Use()
{
    // 데미지 계산
}

shared_ptr<ISkill> EmberSkill::Clone() const
{
    return make_shared<EmberSkill>(*this);  // 스킬을 복제하여 반환
}
