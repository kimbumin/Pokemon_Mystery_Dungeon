#include "SquareScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TilemapTool.h"


#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	redFlower = new Image();
	yellowFlower = new Image();

	//954, 714
	backGround = ImageManager::GetInstance()->AddImage(
		"±¤Àå¹è°æ", L"Image/SceneImage/Square2.bmp", 
		SQUARESIZE_X, SQUARESIZE_Y, 1,1,
		0, RGB(255,0,255));


	//33,144
	yellowFlower = ImageManager::GetInstance()->AddImage(
		"³ë¶õ²É", L"Image/SceneImage/YellowFlower.bmp", 
		33, 144, 1,6,
		0, RGB(184,240,120));
	
	redFlower = ImageManager::GetInstance()->AddImage(
		"ºÓÀº²É", L"Image/SceneImage/RedFlower.bmp", 
		33, 144, 1,6,
		0, RGB(184,240,120));

	redPositions = {
		{545, 128},
		{452, 164},
		{455, 567},
		{42, 239},
		{103, 243},
		{88, 270},
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
		{854, 377},
		{710, 489},
		{738, 524},
		{455, 246},
		{341, 611}
	};
	elapsedTime = 0;
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


	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > 0.1f)
	{
		currAnimaionFrame++;
		if (currAnimaionFrame >= yellowFlower->GetMaxFrameY())
		{
			currAnimaionFrame = 0;
		}
		elapsedTime = 0;
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

    TimerManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));
}


void SquareScene::RenderFlowers(HDC hdc, Image* flower, const std::vector<POINT>& positions, int currFrame) {
    for (const auto& pos : positions) {
        flower->FrameRender(hdc, pos.x, pos.y, 0, currFrame, 0);
    }
}
