#pragma once
#include "ISkill.h"
#include "Image.h"

class AttackSkill : public ISkill
{
private:
    FPOINT pos;
    bool isActive;
    int frameCount;
    float elapsedTime;
    Image* image;
    int direction;

public:
    AttackSkill() = default;
    AttackSkill(const SkillData& skillData);

    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use(PokemonBase* owner) override;
    shared_ptr<ISkill> Clone() override;
};
