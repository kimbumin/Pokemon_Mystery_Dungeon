#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class EmberSkill : public ISkill {
private:
    Image* image;

    enum class ElementType { Fire };
    enum class SkillType { Special };

    FPOINT pos;
    string name;
    struct SkillStats {
        int power;
        int accuracy;
        int maxPP;
    } stats;

public:
    void Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use() override;
    shared_ptr<ISkill> Clone() const override;

    string GetName() const override { return name; }
    string GetElement() const override { return "Fire"; }
    string GetType() const override { return "Special"; }
    int GetPower() const override { return stats.power; }
    int GetAccuracy() const override { return stats.accuracy; }
};
