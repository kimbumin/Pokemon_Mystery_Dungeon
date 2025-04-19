#include "SquareScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TilemapTool.h"
#include "DungeonScene.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	redFlower = new Image();
	yellowFlower = new Image();
	river = new Image();


	player = new PlayerBumin();
	enemy = new EnemyBumin();
	emberSkill = new EmberSkill();

	player->Init(); // 만약 Init 필요하면
	enemy->Init();
	emberSkill->Init();


	//Size : 954, 714
	backGround = ImageManager::GetInstance()->AddImage(
		"광장배경", L"Image/SceneImage/Square3.bmp", 
		SQUARESIZE_X, SQUARESIZE_Y, 1,1,
		0, RGB(255,0,255));

	//210,41
	river = ImageManager::GetInstance()->AddImage(
		"강물", L"Image/SceneImage/river.bmp",
		210, 41, 6, 1,
		0, RGB(200, 224, 168));

	//33,144
	yellowFlower = ImageManager::GetInstance()->AddImage(
		"노란꽃", L"Image/SceneImage/YellowFlower.bmp", 
		33, 144, 1,6,
		0, RGB(184,240,120));
	
	redFlower = ImageManager::GetInstance()->AddImage(
		"붉은꽃", L"Image/SceneImage/RedFlower.bmp", 
		33, 144, 1,6,
		0, RGB(184,240,120));

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
		// 중앙 세로 3개
		{477,  77},
		{477, 110},
		{477, 143},

		// 오른쪽 세로 4개
		{545,  95},
		{545, 128},
		{545, 161},
		{545, 194},

		// 기타 개별 위치
		{353, 578},
		{388,291},
		{854, 377},
		{710, 489},
		{738, 524},
		{455, 246},
		{341, 611},
	};
	elapsedTime = 0;
	return S_OK;
}

void SquareScene::Release()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (enemy)
	{
		delete enemy;
		enemy = nullptr;
	}
	if (emberSkill)
	{
		delete emberSkill;
		emberSkill = nullptr;
	}
}

void SquareScene::Update()
{

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1)) {

		SceneManager::GetInstance()->AddScene("타일맵툴", new TilemapTool());
		SceneManager::GetInstance()->ChangeScene("타일맵툴");
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE)) {
		emberSkill->Use(player, enemy);
	}
	// 스킬 업데이트
	emberSkill->Update();
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

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		SceneManager::GetInstance()->AddScene("던전씬", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("던전씬");
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


	if (player) player->Render(hdc);
	if (enemy) enemy->Render(hdc);
	if (emberSkill) emberSkill->Render(hdc);

    TimerManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));
}


void SquareScene::RenderFlowers(HDC hdc, Image* flower, const std::vector<POINT>& positions, int currFrame) {
    for (const auto& pos : positions) {
        flower->FrameRender(hdc, pos.x, pos.y, 0, currFrame, 0);
    }
}
