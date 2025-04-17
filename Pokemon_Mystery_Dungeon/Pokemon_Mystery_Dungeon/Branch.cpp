#include "Branch.h"

HRESULT Branch::Init()
{
	x = 0; y = 0;
	branchDamage = rand() % 4; // *개선사항 랜덤값데미지가 플레이어가 사용하는객체의 공격력만큼을 곱해줘야함

	name = "Branch";

	image = ImageManager::GetInstance()->AddImage(
		"Branch", TEXT("Image/ItemImage.bmp"), 1, 1, 1, 1,
		true, RGB(255, 0, 255));
}

void Branch::Update()
{
}

void Branch::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("Branch");
	if (image)
	{
		image->FrameRender(hdc, x, y, 1, 0, false, true);
	}
}

void Branch::Release()
{
}

void Branch::Use()
{
}

void Branch::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
