#include "SquareScene.h"

#include "CollisionBoxTool.h"
#include "CommonFunction.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "DungeonScene.h"
#include "Image.h"
#include "LoadingScene.h"
#include "MPlayer.h"
#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "SkillManager.h"
#include "StartScene.h"
#include "TilemapTool.h"
#include "UIManager.h"

#include "Camera.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    UIManager::GetInstance()->Init();

    // Size : 954, 714
    backGround = ImageManager::GetInstance()->AddImage(
        "SquareBackGround", L"Image/SceneImage/Square3.bmp", SQUARESIZE_X,
        SQUARESIZE_Y, 1, 1, 0, RGB(255, 0, 255));

    // 210,41
    river = ImageManager::GetInstance()->AddImage(
        "river", L"Image/SceneImage/river.bmp", 210, 41, 6, 1, 0,
        RGB(200, 224, 168));

    // 33,144
    yellowFlower = ImageManager::GetInstance()->AddImage(
        "yellowFlower", L"Image/SceneImage/YellowFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redFlower = ImageManager::GetInstance()->AddImage(
        "redFlower", L"Image/SceneImage/RedFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redPositions = {
        {545, 128}, {452, 164}, {455, 567}, {42, 239}, {103, 243},
        {85, 266},  {320, 589}, {856, 443}, {76, 293}, {261, 355},
    };
    yellowPositions = {
        // 占쌩억옙 占쏙옙占쏙옙 3占쏙옙
        {477, 77},
        {477, 110},
        {477, 143},

        // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 4占쏙옙
        {545, 95},
        {545, 128},
        {545, 161},
        {545, 194},

        // 占쏙옙타 占쏙옙占쏙옙 占쏙옙치
        {353, 578},
        {388, 291},
        {854, 377},
        {710, 489},
        {738, 524},
        {455, 246},
        {341, 611},
    };


    elapsedTime = 0;

    collisionBoxTool = new CollisionBoxTool();
    collisionBoxTool->Init(L"Square");

    mPlayer = new MPlayer();
    mPlayer->Init();

    Camera::GetInstance()->SetMapSize({SQUARESIZE_X, SQUARESIZE_Y});
    Camera::GetInstance()->SetScreenSize({500, 400});


    return S_OK;
}

void SquareScene::Release()
{
    SkillManager::GetInstance()->ReleaseInstance();

}

void SquareScene::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
    {
        SceneManager::GetInstance()->AddScene("TileMapTool", new TilemapTool());
        SceneManager::GetInstance()->ChangeScene("TileMapTool");
    }


    if (yellowFlower && TimerManager::GetInstance())
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
        if (elapsedTime > 0.3f)
        {
            currAnimaionFrame++;
            if (currAnimaionFrame >= yellowFlower->GetMaxFrameY())
            {
                currAnimaionFrame = 0;
            }
            elapsedTime = 0;
        }
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->AddScene("DungeonScene", new DungeonScene());
        SceneManager::GetInstance()->ChangeScene("DungeonScene","LoadingScene");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F5))
    {
        SceneManager::GetInstance()->AddScene("StartScene", new StartScene());
        SceneManager::GetInstance()->AddLoadingScene("LoadingScene",
                                                     new LoadingScene());
        SceneManager::GetInstance()->ChangeScene("StartScene", "LoadingScene");
    }

    elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
    if (elapsedTime > 0.3f)
    {
        currAnimaionFrame++;
        if (currAnimaionFrame >= yellowFlower->GetMaxFrameY())
        {
            currAnimaionFrame = 0;
        }
        elapsedTime = 0;
    }
    if (collisionBoxTool)
    {
        collisionBoxTool->Update();
        CollisionManager::GetInstance()->MapPlayerCheck( mPlayer, collisionBoxTool->GetRectBoxes());
    }

    if (mPlayer)
    {
        mPlayer->Update();
        Camera::GetInstance()->SetCameraPos(mPlayer->GetPos());

    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
    {
        UIManager::GetInstance()->OpenUIStateBox("defaultUI");
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x49))  // 'I' 키
    {
        DialogueManager::GetInstance()->ShowLine(
            DialogueTemplate::FoundItem, {{L"itemName", L"Monster Ball"}});
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))  // 'D' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("DungeonUI");


        //SetDugeonType이런 거 만들어 줘야되고,
        //DungeonScene이동,
        // 



    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x59))  // 'Y' 키
    {
        UIManager::GetInstance()->OpenUIStateBox("YesOrNoUI");
    }
}

void SquareScene::Render(HDC hdc)
{
    // 카메라 클리핑 처리 (화면 크기: 500x400)
    HRGN clipRegion = CreateRectRgn(0, 0, 500, 400);
    SelectClipRgn(hdc, clipRegion);

    // --- 카메라 기준으로 렌더링되는 오브젝트 ---
    if (backGround)
        backGround->RenderWithCamera(hdc, 0, 0);

    if (yellowFlower)
        RenderFlowers(hdc, yellowFlower, yellowPositions, currAnimaionFrame);

    if (redFlower)
        RenderFlowers(hdc, redFlower, redPositions, currAnimaionFrame);

    if (river)
    {
        river->FrameRenderWithCamera(hdc, 64, 54, currAnimaionFrame, 0,0,1);
        river->FrameRenderWithCamera(hdc, 64, 104, currAnimaionFrame, 0, 0, 1);
        river->FrameRenderWithCamera(hdc, 152, 273, currAnimaionFrame, 0, 0, 1);
        river->FrameRenderWithCamera(hdc, 152, 400, currAnimaionFrame, 0, 0, 1);
        river->FrameRenderWithCamera(hdc, 152, 460, currAnimaionFrame, 0, 0, 1);
    }

    if (collisionBoxTool)
        collisionBoxTool->Render(hdc);

    if (mPlayer)
        mPlayer->Render(hdc);

    // 클리핑 해제
    SelectClipRgn(hdc, NULL);
    DeleteObject(clipRegion);

    // --- UI, 디버그 텍스트 등은 카메라에 영향을 받지 않음 ---
    TimerManager::GetInstance()->Render(hdc);
    UIManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));

}

void SquareScene::RenderFlowers(HDC hdc, Image* flower,const std::vector<POINT>& positions, int currFrame)
{
    for (const POINT& pos : positions)
    {
        flower->FrameRenderWithCamera(hdc, pos.x, pos.y, 0, currFrame,0, 1);
    }
}
