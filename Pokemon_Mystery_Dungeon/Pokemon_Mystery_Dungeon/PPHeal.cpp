#include "PPHeal.h"
#include "ISkill.h"

HRESULT PPHeal::Init()
{
	x = 0; y = 0;

	healPP = 10; // *개선사항 : pp값을 플레이어가 사용하는 스킬의 남은 PP값을 가져와서 수치만큼 더해줌
	name = "PPHeal";

	image = ImageManager::GetInstance()->AddImage(
		"PPHeal", TEXT("Image/ItemImage.bmp"), 1, 1, 1, 1,
		true, RGB(255, 0, 255));
}

void PPHeal::Update()
{
}

void PPHeal::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("PPHeal");
	if (image)
	{
		image->FrameRender(hdc, x, y, 1, 0, false, true);
	}
}

void PPHeal::Release()
{
}

void PPHeal::Use()
{
	//플레이어가 가지고 있는 스킬의 PP값을 가져와서 += healPP;
}

void PPHeal::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
