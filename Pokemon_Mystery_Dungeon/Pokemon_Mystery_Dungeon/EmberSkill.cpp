#include "EmberSkill.h"
#include "PokemonBase.h"

HRESULT EmberSkill::Init()
{
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

void EmberSkill::Use(PokemonBase* owner) const
{
	//direction = static_cast<int>(owner->GetDirection());
	//pos = owner->GetPos();

	//auto dirIndex = static_cast<size_t>(direction);
	//pos.x += directionOffsets[dirIndex].first;
	//pos.y += directionOffsets[dirIndex].second;

	//isActive = true;
}




shared_ptr<ISkill> EmberSkill::Clone() const
{
	return make_shared<EmberSkill>(*this); // 스킬을 복제하여 반환
}
