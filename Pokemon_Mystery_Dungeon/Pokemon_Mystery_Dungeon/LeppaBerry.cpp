#include "LeppaBerry.h"

HRESULT LeppaBerry::Init()
{
	x = 0; y = 0;
	healPP = 10;
	name = "LeppaBerry";

	image = ImageManager::GetInstance()->AddImage(
		"LeppaBerry", L"Image/ItemImage/LeppaBerry.bmp",
		12, 12, 1, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void LeppaBerry::Update()
{
}

void LeppaBerry::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("LeppaBerry");
	if (image)
	{
		image->FrameRender(hdc, x, y, 0, 0, false, true);
	}
}

void LeppaBerry::Release()
{
}

void LeppaBerry::Use()
{
}

void LeppaBerry::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
