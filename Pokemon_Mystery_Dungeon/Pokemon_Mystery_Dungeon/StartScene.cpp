#include "StartScene.h"

#include "CommonFunction.h"
#include "ImageGDIPlus.h"
#include "ImageGDIPlusManager.h"
#include "SquareScene.h"
#include "FadeManager.h"
HRESULT StartScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);  // 인트로 애니메이션사이즈 1280*720
    currFrameIndex = 0;
    elapsedTime = 0.0f;

    for (int i = 82; i <= 816; ++i)
    {
        wchar_t filename[256];
        swprintf(filename, 256,
                 L"Image/SceneImage/intro_animation/teset-%04d.png", i);

        std::string key = "introFrame" + std::to_string(i);
        ImageGDIPlus* frame =
            ImageGDIPlusManager::GetInstance()->AddImage(key, filename);

        if (frame)
        {
            introFrames.push_back(frame);
        }
    }

    return S_OK;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsedTime > 0.033f)
    {
        FadeManager::GetInstance()->Update();
        currFrameIndex++;
        if (currFrameIndex >= introFrames.size())
        {
            currFrameIndex = introFrames.size() - 1;
        }
        elapsedTime = 0;
    }
    if (isSceneTransition && FadeManager::GetInstance()->IsFadeComplete())
    {
        isSceneTransition = false;
        SceneManager::GetInstance()->ChangeScene("Square");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE) &&
        !FadeManager::GetInstance()->IsFading())
    {
        FadeManager::GetInstance()->StartFadeOut(1.0);
        isSceneTransition = true;
    }
}

void StartScene::Render(HDC hdc)
{
    if (!introFrames.empty() && currFrameIndex < introFrames.size())
    {
        introFrames[currFrameIndex]->RenderScale(
            hdc, -13, -5, 0.65, 0.6);  // 800* 400  1280*720 사이즈로 맞추려면,
    }
    FadeManager::GetInstance()->Render(hdc, WINSIZE_X, WINSIZE_Y);
}

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}
