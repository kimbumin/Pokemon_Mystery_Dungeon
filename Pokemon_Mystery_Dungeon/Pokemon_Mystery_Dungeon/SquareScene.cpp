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
	//954, 714
	if (FAILED(backGround->Init(TEXT("Image/SceneImage/Square.bmp"), SQUARESIZE_X, SQUARESIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
		return E_FAIL;
	}


	return S_OK;

}

void SquareScene::Release()
{

}

void SquareScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1)) {

		SceneManager::GetInstance()->AddScene("타일맵툴", new TilemapTool());
		SceneManager::GetInstance()->ChangeScene("타일맵툴");

	}
}

void SquareScene::Render(HDC hdc)
{
	backGround->Render(hdc);

}
