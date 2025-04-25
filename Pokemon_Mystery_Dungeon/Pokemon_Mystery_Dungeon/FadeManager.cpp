#include "FadeManager.h"
#pragma comment(lib, "Msimg32.lib")  

FadeManager::FadeManager()
    : alpha(0.0f),
      isFading(false),
      fadeOut(true),
      fadeSpeed(5.0f),
      fadeColor(RGB(0, 0, 0))  
{
}

void FadeManager::StartFadeOut(float speed)
{
    fadeOut = true;
    isFading = true;
    alpha = 0.0f;
    fadeSpeed = speed;
}

void FadeManager::StartFadeIn(float speed)
{
    fadeOut = false;
    isFading = true;
    alpha = 1.0f;
    fadeSpeed = speed;
}

void FadeManager::Update()
{
    if (!isFading)
        return;

    float delta = fadeSpeed * 0.016f;
    if (fadeOut)
    {
        alpha += delta;
        if (alpha >= 1.0f)
        {
            alpha = 1.0f;
            isFading = false;
        }
    }
    else
    {
        alpha -= delta;
        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            isFading = false;
        }
    }
}

void FadeManager::Render(HDC hdc, int width, int height)
{
    if (alpha <= 0.0f)
        return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP fadeBitmap = CreateCompatibleBitmap(hdc, width, height);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, fadeBitmap);

    HBRUSH brush = CreateSolidBrush(fadeColor);
    RECT rect = {0, 0, width, height};
    FillRect(memDC, &rect, brush);
    DeleteObject(brush);

    BLENDFUNCTION blend = {AC_SRC_OVER, 0, (BYTE)(alpha * 255), 0};
    AlphaBlend(hdc, 0, 0, width, height, memDC, 0, 0, width, height, blend);

    SelectObject(memDC, oldBitmap);
    DeleteObject(fadeBitmap);
    DeleteDC(memDC);
}
bool FadeManager::IsFading() const
{
    return isFading;
}

bool FadeManager::IsFadeComplete() const
{
    return !isFading;
}
