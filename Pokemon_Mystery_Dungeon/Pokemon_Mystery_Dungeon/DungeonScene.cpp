#include "DungeonScene.h"

#include "BossScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MPlayer.h"
#include "UIManager.h"
#include "Camera.h"


HRESULT DungeonScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    mPlayer = new MPlayer;
    mPlayer->Init();

    Camera::GetInstance()->SetMapSize({TILE_X * TILE_SIZE, TILE_Y * TILE_SIZE});
    Camera::GetInstance()->SetScreenSize({500, 400});

    wallTiles = map.GetWallTiles();  // wallTiles좌표  Point로

    dungeonFloor = 0;

    GenerateNextFloor();

    return S_OK;
}

void DungeonScene::Release()
{
    if (mPlayer)
    {
        mPlayer->Release();
        delete mPlayer;
        mPlayer = nullptr;
    }
}

void DungeonScene::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("Square");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
    {
        GenerateNextFloor();
    }
    if (dungeonFloor > 5)
    {
        dungeonFloor = 0;
        SceneManager::GetInstance()->AddScene("BossScene", new BossScene());
        SceneManager::GetInstance()->ChangeScene("BossScene");
    }

    if (mPlayer)
    {
        mPlayer->Update();
        Camera::GetInstance()->SetCameraPos(mPlayer->GetPos());

        if (IsPlayerOnStair())
        {
            ++dungeonFloor;
            GenerateNextFloor();
        }
    }
}

void DungeonScene::Render(HDC hdc)
{
    HRGN clipRegion = CreateRectRgn(0, 0, 500, 400);
    SelectClipRgn(hdc, clipRegion);

    map.RenderWithCamera(hdc);
    map.MiniMapRender(hdc, 0, 0);


    if (mPlayer)
    {
        mPlayer->Render(hdc);
    }
    SelectClipRgn(hdc, NULL);
    DeleteObject(clipRegion);


    //UI등 clip영역 밖에 추가하실거면 이 밑에 두세요 --
    UIManager::GetInstance()->Render(hdc);
}

void DungeonScene::GenerateNextFloor()
{
    map.Init();
    wallTiles = map.GetWallTiles();
    stairPos = ConvertToPixel(map.GetStairPos());
}

POINT DungeonScene::ConvertToPixel(POINT tilePos)
{
    tilePos.x *= TILE_SIZE;
    tilePos.y *= TILE_SIZE;
    return tilePos;
}

bool DungeonScene::IsPlayerOnStair()
{
    POINT playerPos = mPlayer->GetPos();
    return abs(playerPos.x - stairPos.x) <= TILE_SIZE &&
           abs(playerPos.y - stairPos.y) <= TILE_SIZE;
}