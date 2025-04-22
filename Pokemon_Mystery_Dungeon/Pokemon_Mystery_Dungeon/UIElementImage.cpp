#include "UIElementImage.h"

void UIElementImage::SetSpeed(float speed)
{
    if (imageGDIPlus)
    {
        imageGDIPlus->SetGifSpeed(speed);
    }
}

void UIElementImage::Render(HDC hdc)
{
    if (!imageGDIPlus && !image)
        return;

    FPOINT pos = GetRealPos();

    if (imageGDIPlus)
    {
        imageGDIPlus->RenderScale(hdc, pos.x, pos.y, scaleX, scaleY, angle,
                                  flipX, flipY, alpha);
    }
    else if (image)
    {
        image->Render(hdc, pos.x, pos.y);
    }

    for (auto child : children)
    {
        child->Render(hdc);
    }
}

void UIElementImage::Update()
{
    if (imageGDIPlus)
    {
        imageGDIPlus->Update(TimerManager::GetInstance()->GetDeltaTime());
    }
    UIElement::Update();
}
