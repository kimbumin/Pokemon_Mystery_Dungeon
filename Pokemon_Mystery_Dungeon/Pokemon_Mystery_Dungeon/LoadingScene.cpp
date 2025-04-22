#include "LoadingScene.h"
#include <string>
#include "CommonFunction.h"
LoadingScene::LoadingScene(): frameCount(0)
{
}

LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    frameCount = 0;
    return S_OK;
}

void LoadingScene::Release()
{

}

void LoadingScene::Update()
{
    frameCount++;
    if (frameCount > 180) frameCount = 0; // 최대 3초까지
}

void LoadingScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, 2000, 2000, BLACKNESS);

    std::string text = "Loading";
    int dotCount = (frameCount / 60) % 4; // 0 ~ 3
    for (int i = 0; i < dotCount; ++i)
    {
        text += ".";
    }

    TextOutA(hdc, 300, 300, text.c_str(), static_cast<int>(text.length()));




}
