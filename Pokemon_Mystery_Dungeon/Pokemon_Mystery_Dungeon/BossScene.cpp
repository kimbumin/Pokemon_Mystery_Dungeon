#include "BossScene.h"

#include "CollisionBoxTool.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Camera.h"

HRESULT BossScene::Init()
{
    collisionBoxTool = new CollisionBoxTool();
    collisionBoxTool->Init(L"MagmaBossRoom");

    backGroundWidth = 432;
    backGroundHeight = 376;

    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    {
        backGround = ImageManager::GetInstance()->AddImage(
            "MagmaBossMap", L"Image/SceneImage/MagmaBossMap.bmp", backGroundWidth,
            backGroundHeight, 1, 1, true, RGB(255, 0, 255));
    }

    mPlayer = new MPlayer;
    mPlayer->Init();
    mPlayer->SetPos({180,160});

    Camera::GetInstance()->SetMapSize({TILE_X * TILE_SIZE, TILE_Y * TILE_SIZE});
    Camera::GetInstance()->SetScreenSize({500, 400});

    InitBoss();

    return S_OK;
}

void BossScene::Release()
{
    if (mPlayer)
    {
        mPlayer->Release();
        delete mPlayer;
        mPlayer = nullptr;
    }

    // if (boss) {
    //	boss->Release();
    //	delete boss;
    //	boss = nullptr;
    // }
}

void BossScene::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("Square");
    }

    if (mPlayer)
    {
        mPlayer->Update();
        Camera::GetInstance()->SetCameraPos(mPlayer->GetPos());
    }
    // if (boss) boss->Update();

    if (BossScene::IsBossDefeated())
    {
        SceneManager::GetInstance()->ChangeScene("Square");
    }

    if (collisionBoxTool)
    {
        collisionBoxTool->Update();
        CollisionManager::GetInstance()->MapPlayerCheck(
            mPlayer, collisionBoxTool->GetRectBoxes());
    }
}

void BossScene::Render(HDC hdc)
{
    HRGN clipRegion = CreateRectRgn(0, 0, 500, 400);
    SelectClipRgn(hdc, clipRegion);

    backGround->RenderWithCamera(hdc, 0, 0);

    if (mPlayer)
        mPlayer->Render(hdc);
    // if (boss) boss->Render(hdc);
    if (collisionBoxTool)
    {
        collisionBoxTool->Render(hdc);
    }
    SelectClipRgn(hdc, NULL);
    DeleteObject(clipRegion);

}

void BossScene::InitBoss()
{
    // boss = new BossMonster;
    // bossSpawnPos = { TILE_X / 2 * TILE_SIZE, TILE_Y / 4 * TILE_SIZE }; //
    // 대충 중앙 위쪽 boss->Init(bossSpawnPos);
}

bool BossScene::IsBossDefeated()
{
    // return boss && boss->IsDead();
    return false;
}

void BossScene::CheckBattleEnd()
{
    // 대충 ~ 끝나면 씬 띄워도되고 광장으로 이동해도되고.
}
