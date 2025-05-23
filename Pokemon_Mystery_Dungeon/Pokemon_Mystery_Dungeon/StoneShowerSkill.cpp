#include "StoneShowerSkill.h"

#include "PokemonBase.h"
#include "Camera.h"
#include "BattleSystem.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "CommonFunction.h"
StoneShowerSkill::StoneShowerSkill(const SkillData& skillData)
{
    data = skillData;
    direction = 0;
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = ImageManager::GetInstance()->AddImage(
        "StoneShower", TEXT("Image/SkillImage/StoneShower.bmp"), 312, 54, 8, 1,
        true, RGB(255, 0, 255));
}

HRESULT StoneShowerSkill::Init()
{
    return S_OK;
}

void StoneShowerSkill::Release()
{
}

void StoneShowerSkill::Update()
{
    if (isActive)
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();  // 누적

        if (elapsedTime >= (1.f / image->GetMaxFrameX()))  // 0.2초마다 실행
        {
            frameCount++;
            elapsedTime = 0.0f;  // 다시 0으로 초기화
        }

        if (frameCount >= image->GetMaxFrameX())
        {
            isActive = false;
            frameCount = 0;
        }
    }
}

void StoneShowerSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRenderWithCamera(hdc, pos.x, pos.y, frameX, 0, 0, true);
    }
}

void StoneShowerSkill::Use(PokemonBase* owner)
{
    direction = static_cast<int>(owner->GetDirection());
    pos = owner->GetPos();
    auto dirIndex = static_cast<size_t>(direction);

    pos.x += directionOffsets[dirIndex].first * 24;
    pos.y += directionOffsets[dirIndex].second * 24;
    Camera::GetInstance()->Shake(0.1f, 5);
    isActive = true;

    PokemonBase* target = BattleSystem::GetInstance()->GetTargetInFront(owner);
    if (target)
    {
        int damage =
            BattleSystem::GetInstance()->CalculateDamage(owner, target, this);
        DialogueManager::GetInstance()->ShowLine(
            DialogueTemplate::TookDamage,
            {
                {L"targetName", ToWString(target->GetCurrentPokemonData().name)},
                {L"damage", ToWString(damage)}
            }
        );
        target->TakeDamage(damage);
    }
}

shared_ptr<ISkill> StoneShowerSkill::Clone()
{
    return make_shared<StoneShowerSkill>(*this);  // 스킬을 복제하여 반환
}
void StoneShowerSkill::Reset()
{
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
}