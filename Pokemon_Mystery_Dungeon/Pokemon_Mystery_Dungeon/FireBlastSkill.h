#pragma once
#include "ISkill.h"
// clang-format off
#include "config.h"
// clang-format on
#include "Image.h"

class Image;
class PokemonBase;
class FireBlastSkill : public ISkill
{
private:
    Image* image;
    float elapsedTime;
    int frameCount;

public:
    FireBlastSkill() = default;
    FireBlastSkill(const SkillData& skillData);

    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use(PokemonBase* owner) override;
    shared_ptr<ISkill> Clone() override;
};
