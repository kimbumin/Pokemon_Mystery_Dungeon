#pragma once
#include "ISkill.h"

class SwingSkill : public ISkill
{
private:
    FPOINT pos;
    bool isActive;
    int frameCount;
    float elapsedTime;
    Image* image;
    int direction;

public:
    SwingSkill() = default;
    SwingSkill(const SkillData& skillData);

    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use(PokemonBase* owner) override;
    shared_ptr<ISkill> Clone() override;
    void Reset() override;
};
