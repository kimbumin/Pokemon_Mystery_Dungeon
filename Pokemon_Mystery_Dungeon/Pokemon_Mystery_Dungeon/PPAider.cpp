#include "PPAider.h"

HRESULT PPAider::Init()
{
	x = 0; y = 0;

	healPP = 10;
	name = "PPAider";

	image = ImageManager::GetInstance()->AddImage(
		"PPAider", TEXT("Image/ItemImage.bmp"), 1, 1, 1, 1,
		true, RGB(255, 0, 255));
}

void PPAider::Update()
{
}

void PPAider::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("PPAider");
	if (image)
	{
		image->FrameRender(hdc, x, y, 1, 0, false, true);
	}
}

void PPAider::Release()
{
}

void PPAider::Use()
{	
	//플레이어가 가지고 있는 스킬의 PP값을 가져와서 += healPP;
}

void PPAider::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
