#include "BoltSkill.h"

#include "BattleSystem.h"
#include "Camera.h"
#include "CommonFunction.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "PokemonBase.h"

BoltSkill::BoltSkill(const SkillData& skillData)
{
    data = skillData;
    direction = 0;
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = ImageManager::GetInstance()->AddImage(
        "BoltSkill", TEXT("Image/SkillImage/BoltSkill.bmp"), 360, 60, 6, 1,
        true, RGB(255, 0, 255));
}

HRESULT BoltSkill::Init()
{
    return S_OK;
}

void BoltSkill::Release()
{
}

void BoltSkill::Update()
{
    if (isActive)
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

        if (elapsedTime >= (1.f / image->GetMaxFrameX()))
        {
            frameCount++;
            elapsedTime = 0.0f;
        }

        if (frameCount >= image->GetMaxFrameX())
        {
            isActive = false;
            frameCount = 0;
        }
    }
}

void BoltSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRenderWithCamera(hdc, pos.x, pos.y, frameX, 0, 0, true);
    }
}

void BoltSkill::Use(PokemonBase* owner)
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
            {{L"targetName", ToWString(target->GetCurrentPokemonData().name)},
             {L"damage", ToWString(damage)}});
        target->TakeDamage(damage);
    }
}

shared_ptr<ISkill> BoltSkill::Clone()
{
    return make_shared<BoltSkill>(*this);  // 스킬을 복제하여 반환
}

void BoltSkill::Reset()
{
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
}
