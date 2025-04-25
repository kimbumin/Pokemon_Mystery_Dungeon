#include "OranBerry.h"

HRESULT OranBerry::Init()
{
    x = 0;
    y = 0;
    healHP = 10;
    name = "OranBerry";

    image = ImageManager::GetInstance()->AddImage(
        "OranBerry", L"Image/ItemImage/Oran_Berry.bmp", 12, 12, 1, 1, true,
        RGB(255, 0, 255));

    return S_OK;
}

void OranBerry::Update()
{
}

void OranBerry::Render(HDC hdc)
{
    image = ImageManager::GetInstance()->FindImage("OranBerry");
    if (image)
    {
        image->FrameRender(hdc, x, y, 0, 0, false, true);
    }
}

void OranBerry::Release()
{
}

void OranBerry::Use()
{
    // 플레이어 Hp가져와서 += healHP;
}

void OranBerry::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}
