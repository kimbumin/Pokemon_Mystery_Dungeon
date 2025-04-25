#include "TileMapTestScene.h"

#include "CommonFunction.h"
#include "DungeonScene.h"
#include "Image.h"
#include "ImageGDIPlus.h"
#include "TilemapTool.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT TileMapTestScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    backGround = new Image();
    redFlower = new Image();
    yellowFlower = new Image();
    river = new Image();

    // Size : 954, 714
    backGround = ImageManager::GetInstance()->AddImage(
        "SquareBackGround", L"Image/SceneImage/Square3.bmp", SQUARESIZE_X, SQUARESIZE_Y,
        1, 1, 0, RGB(255, 0, 255));

    // 210,41
    river = ImageManager::GetInstance()->AddImage(
        "river", L"Image/SceneImage/river.bmp", 210, 41, 6, 1, 0,
        RGB(200, 224, 168));

    // 33,144
    yellowFlower = ImageManager::GetInstance()->AddImage(
        "노란꽃", L"Image/SceneImage/YellowFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redFlower = ImageManager::GetInstance()->AddImage(
        "붉은꽃", L"Image/SceneImage/RedFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redPositions = {
        {545, 128}, {452, 164}, {455, 567}, {42, 239}, {103, 243},
        {85, 266},  {320, 589}, {856, 443}, {76, 293}, {261, 355},
    };
    yellowPositions = {
        // 중앙 세로 3개
        {477, 77},
        {477, 110},
        {477, 143},

        // 오른쪽 세로 4개
        {545, 95},
        {545, 128},
        {545, 161},
        {545, 194},

        // 기타 개별 위치
        {353, 578},
        {388, 291},
        {854, 377},
        {710, 489},
        {738, 524},
        {455, 246},
        {341, 611},
    };

    /* ------------------------------------------------------------------------
     */
    // 카메라 초기화 추가
    CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y,
                                       backGround->GetWidth(),
                                       backGround->GetHeight());
    /* ------------------------------------------------------------------------
     */

    elapsedTime = 0;
    return S_OK;
}

void TileMapTestScene::Release()
{
}

void TileMapTestScene::Update()
{
    /* ------------------------------------------------------------------------
     */
    // 마우스 좌표를 가져와서 카메라 위치 설정
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient(g_hWnd, &mouse);
    CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);
    /* ------------------------------------------------------------------------
     */

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
    {
        SceneManager::GetInstance()->ChangeScene("TileMapTool");
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

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("DungeonScene");
    }
}

void TileMapTestScene::Render(HDC hdc)
{
    /* ------------------------------------------------------------------------
     */
    // 배경 그리기 방식 ImageGDIPlus -> Image로 변경 (GDI+와 GDI의 역할 분리)
    // RenderBackground()를 Image로 옮긴 이유 :
    //		대부분 Scene에서 Image클래스를 사용하기 때문
    //		옮기지 않으면 소스코드를 너무 많이 수정해야했음..
    if (backGround)
    {
        backGround->RenderBackground(hdc);
    }
    /* ------------------------------------------------------------------------
     */

    if (yellowFlower)
    {
        RenderFlowers(hdc, yellowFlower, yellowPositions, currAnimaionFrame);
    }
    if (redFlower)
    {
        RenderFlowers(hdc, redFlower, redPositions, currAnimaionFrame);
    }

    RECT cam = CameraManager::GetInstance()->GetViewPos();

    if (river)
    {
        /* ------------------------------------------------------------------------
         */

        // 강물 위치 카메라 따라가게 설정
        // river->FrameRender(hdc, 64 - cam.left, 54 - cam.top,
        // currAnimaionFrame, 0, 0); river->FrameRender(hdc, 64 - cam.left, 104
        // - cam.top, currAnimaionFrame, 0, 0); river->FrameRender(hdc, 152 -
        // cam.left, 273 - cam.top, currAnimaionFrame, 0, 0);
        // river->FrameRender(hdc, 152 - cam.left, 400 - cam.top,
        // currAnimaionFrame, 0, 0); river->FrameRender(hdc, 152 - cam.left, 460
        // - cam.top, currAnimaionFrame, 0, 0);
        /* ------------------------------------------------------------------------
         */
    }

    TimerManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));
}

void TileMapTestScene::RenderFlowers(HDC hdc, Image* flower,
                                     const std::vector<POINT>& positions,
                                     int currFrame)
{
    RECT cam = CameraManager::GetInstance()->GetViewPos();

    for (const auto& pos : positions)
    {
        /* ------------------------------------------------------------------------
         */
        // 꽃 위치 카메라 따라가게 설정
        int flowerX = pos.x - cam.left;
        int flowerY = pos.y - cam.top;

        flower->FrameRender(hdc, flowerX, flowerY, 0, currFrame, 0);

        /* ------------------------------------------------------------------------
         */
    }
}
