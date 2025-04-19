#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class EmberSkill : public ISkill {
private:
    Image* image;

    enum class ElementType { FIRE };
    enum class SkillType { SPECIAL };

    FPOINT pos;
    string name;
    struct SkillStats {
        int power;
        int accuracy;
        int maxPP;
    } stats;

    float elapsedTime;
    bool isActive;  // 스킬 효과가 활성화되어 있는지 여부
    int frameCount;  // 애니메이션 프레임 카운트 (필요한 경우)

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use(PlayerBumin* user, EnemyBumin* target) override;
    shared_ptr<ISkill> Clone() const override;

    string GetName() const override { return name; }
    string GetElement() const override { return "FIRE"; }
    string GetType() const override { return "SPECIAL"; }
    int GetPower() const override { return stats.power; }
    int GetAccuracy() const override { return stats.accuracy; }
};
