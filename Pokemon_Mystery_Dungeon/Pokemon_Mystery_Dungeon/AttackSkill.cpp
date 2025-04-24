#include "AttackSkill.h"

#include "PokemonBase.h"
#include "BattleSystem.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "CommonFunction.h"
AttackSkill::AttackSkill(const SkillData& skillData)
{
    data = skillData;
    direction = 0;
    pos = {0, 0};
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
    image = nullptr;
}

HRESULT AttackSkill::Init()
{

    return S_OK;
}

void AttackSkill::Release()
{
}

void AttackSkill::Update()
{
    if (isActive)
    {
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

        if (elapsedTime >= 1.f)
        {
            isActive = false;
            elapsedTime = 0;
        }
    }
}

void AttackSkill::Render(HDC hdc)
{
    if (isActive && image)
    {
        int frameX = frameCount;
        if (frameX >= image->GetMaxFrameX())
            frameX = image->GetMaxFrameX() - 1;

        image->FrameRender(hdc, pos.x, pos.y, frameX, 0);
    }
}

void AttackSkill::Use(PokemonBase* owner)
{
    direction = static_cast<int>(owner->GetDirection());
    pos = owner->GetPos();
    auto dirIndex = static_cast<size_t>(direction);

    pos.x += directionOffsets[dirIndex].first * 24;
    pos.y += directionOffsets[dirIndex].second * 24;

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

shared_ptr<ISkill> AttackSkill::Clone()
{
    return make_shared<AttackSkill>(*this);
}
void AttackSkill::Reset()
{
    isActive = false;
    frameCount = 0;
    elapsedTime = 0.0f;
}