#include "SquareScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TilemapTool.h"


#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
	SetClientRect(g_hWnd, SQUARESIZE_X, SQUARESIZE_Y -14);

	backGround = new Image();
	redFlower = new Image();
	yellowFlower = new Image();

	//954, 714
	backGround = ImageManager::GetInstance()->AddImage(
		"±¤Àå¹è°æ", L"Image/SceneImage/Square.bmp", 
		SQUARESIZE_X, SQUARESIZE_Y, 1,1,
		0, RGB(255,0,255));


	//33,144
	yellowFlower = ImageManager::GetInstance()->AddImage(
		"³ë¶û²É", L"Image/SceneImage/YellowFlower.bmp", 
		33, 144, 1,6,
		0, RGB(184,240,120));


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
		yellowFlower->FrameRender(hdc, SQUARESIZE_X /2, SQUARESIZE_Y /2, 0, currAnimaionFrame, 0);
	}

}
