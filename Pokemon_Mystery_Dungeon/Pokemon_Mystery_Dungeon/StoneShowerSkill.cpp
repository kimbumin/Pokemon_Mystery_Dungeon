#include "StoneShowerSkill.h"

void StoneShowerSkill::Init()
{
	pos.x = 0;
	pos.y = 0;
	name = "StoneShower";
	stats.power = 75;
	stats.accuracy = 90;
	stats.maxPP = 10;

	image = ImageManager::GetInstance()->AddImage(
		"StoneShower", TEXT("Image/rocktype1.bmp"), 312, 54, 8, 1,
		true, RGB(255, 0, 255));
}

void StoneShowerSkill::Release()
{
}

void StoneShowerSkill::Update()
{
}

void StoneShowerSkill::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("StoneShower");
	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
	}
}

void StoneShowerSkill::Use()
{
}

shared_ptr<ISkill> StoneShowerSkill::Clone() const
{
	return make_shared<StoneShowerSkill>(*this);	//스킬을 복제하여 반환
}
