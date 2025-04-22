#include "SquareScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TilemapTool.h"
#include "DungeonScene.h"
#include "StartScene.h"
#include "LoadingScene.h"
#include "CollisionBoxTool.h"
#include "MPlayer.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	{
		//Size : 954, 714
		backGround = ImageManager::GetInstance()->AddImage(
			"±¤Àå¹è°æ", L"Image/SceneImage/Square3.bmp",
			SQUARESIZE_X, SQUARESIZE_Y, 1, 1,
			0, RGB(255, 0, 255));

		//210,41
		river = ImageManager::GetInstance()->AddImage(
			"°­¹°", L"Image/SceneImage/river.bmp",
			210, 41, 6, 1,
			0, RGB(200, 224, 168));

		//33,144
		yellowFlower = ImageManager::GetInstance()->AddImage(
			"³ë¶õ²É", L"Image/SceneImage/YellowFlower.bmp",
			33, 144, 1, 6,
			0, RGB(184, 240, 120));

		redFlower = ImageManager::GetInstance()->AddImage(
			"ºÓÀº²É", L"Image/SceneImage/RedFlower.bmp",
			33, 144, 1, 6,
			0, RGB(184, 240, 120));
	}

	redPositions = {
		{545, 128},
		{452, 164},
		{455, 567},
		{42, 239},
		{103, 243},
		{85, 266},
		{320, 589},
		{856, 443},
		{76,293},
		{261,355},
	};
	yellowPositions = {
		// Áß¾Ó ¼¼·Î 3°³
		{477,  77},
		{477, 110},
		{477, 143},

		// ¿À¸¥ÂÊ ¼¼·Î 4°³
		{545,  95},
		{545, 128},
		{545, 161},
		{545, 194},

		// ±âÅ¸ °³º° À§Ä¡
		{353, 578},
		{388,291},
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


	return S_OK;
}

void SquareScene::Release()
{

}

void SquareScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1)) {

		SceneManager::GetInstance()->AddScene("Å¸ÀÏ¸ÊÅø", new TilemapTool());
		SceneManager::GetInstance()->ChangeScene("Å¸ÀÏ¸ÊÅø");
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
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		SceneManager::GetInstance()->AddScene("´øÀü¾À", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("´øÀü¾À", "·Îµù¾À");
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F5)) {
		SceneManager::GetInstance()->AddScene("½ºÅ¸Æ®¾À", new StartScene());
		SceneManager::GetInstance()->AddLoadingScene("·Îµù¾À", new LoadingScene());
		SceneManager::GetInstance()->ChangeScene("½ºÅ¸Æ®¾À", "·Îµù¾À");
	}

	if (collisionBoxTool) {
		collisionBoxTool->Update();
		CollisionManager::GetInstance()->MapPlayerCheck(mPlayer, collisionBoxTool->GetRectBoxes());
	}

	if (mPlayer) {
		mPlayer->Update();
	}
	
	
}


void SquareScene::Render(HDC hdc)
{
    if (backGround) {
        backGround->Render(hdc);
    }
    if (yellowFlower) {
        RenderFlowers(hdc, yellowFlower, yellowPositions, currAnimaionFrame);
    }
    if (redFlower) {
        RenderFlowers(hdc, redFlower, redPositions, currAnimaionFrame);
    }
	if (river) {
		river->FrameRender(hdc, 64, 54, currAnimaionFrame, 0, 0);
		river->FrameRender(hdc, 64, 104, currAnimaionFrame, 0, 0);
		river->FrameRender(hdc, 152, 273, currAnimaionFrame, 0, 0);
		river->FrameRender(hdc, 152, 400, currAnimaionFrame, 0, 0);
		river->FrameRender(hdc, 152, 460, currAnimaionFrame, 0, 0);

	}
	if (collisionBoxTool) {
		collisionBoxTool->Render(hdc);
	}
	if (mPlayer) {
		mPlayer->Render(hdc);
	}

    TimerManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));
}


void SquareScene::RenderFlowers(HDC hdc, Image* flower, const std::vector<POINT>& positions, int currFrame) {
    for (const auto& pos : positions) {
        flower->FrameRender(hdc, pos.x, pos.y, 0, currFrame, 0);
    }
}
