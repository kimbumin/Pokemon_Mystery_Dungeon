#include "EmberSkill.h"
#include "config.h"

void EmberSkill::Init()
{
    image = ImageManager::GetInstance()->AddImage(
        "", L"", 64, 64,
        true, RGB(255, 0, 255));
}

void EmberSkill::Release()
{
}

void EmberSkill::Update()
{
}

void EmberSkill::Render(HDC hdc)
{
}

void EmberSkill::Use()
{
}
