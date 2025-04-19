#include "EmberSkill.h"

HRESULT EmberSkill::Init()
{
	pos.x = 100;
	pos.y = 100;
	name = "Ember";
	stats.power = 40;
	stats.accuracy = 100;
	stats.maxPP = 25;

	isActive = false;
	frameCount = 0;
	elapsedTime = 0.0f;
	image = ImageManager::GetInstance()->AddImage(
		"Ember", TEXT("Image/SkillImage/FireBlast.bmp"), 1856*2, 61*2 ,29, 1,
		true, RGB(255, 0, 255));

	return S_OK;
}

void EmberSkill::Release()
{
}

// EmberSkill::Update() 안 예시
void EmberSkill::Update()
{
	if (isActive)
	{
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime(); // 누적

		if (elapsedTime >= 0.02f) // 0.2초마다 실행
		{
			frameCount++;
			elapsedTime = 0.0f; // 다시 0으로 초기화
		}

		if (frameCount >= image->GetMaxFrameX())
		{
			isActive = false;
			frameCount = 0;
		}
	}
}



void EmberSkill::Render(HDC hdc)
{
	if (isActive && image)
	{
		int frameX = frameCount;
		if (frameX >= image->GetMaxFrameX()) frameX = image->GetMaxFrameX() - 1;

		image->FrameRender(hdc, pos.x, pos.y, frameX, 0);
	}
}


void EmberSkill::Use(PlayerBumin* user, EnemyBumin* target)
{
	pos.x = target->GetX();
	pos.y = target->GetY();
	int emberDamage = 10; //fix 데미지 계산 식 수정 필요

	int newHP = target->GetHP() - emberDamage;
	if (newHP < 0)
		newHP = 0;

	target->SetHP(newHP);

	// 스킬 효과 활성화
	isActive = true;
}


shared_ptr<ISkill> EmberSkill::Clone() const
{
	return make_shared<EmberSkill>(*this); // 스킬을 복제하여 반환
}
