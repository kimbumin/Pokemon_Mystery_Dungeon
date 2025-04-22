#pragma once
#include "GameObject.h"

struct SkillData {
    int number;
    string name;
    string element;
    string type;
    string animAction;
    int power;
    int accuracy;
    int pp;
};

class PokemonBase;

class ISkill : public GameObject {
protected:
    SkillData data;
    FPOINT pos;
    int direction;
    bool isActive;

public:
    //ISkill() = default;
    //ISkill(const SkillData& skillData) : data(skillData) {}

    virtual HRESULT Init() const = 0;
    virtual void Release() const = 0;
    virtual void Update() const = 0;
    virtual void Render(HDC hdc) const = 0;
    virtual void Use(PokemonBase* owner) const = 0;
    virtual shared_ptr<ISkill> Clone() const = 0;

    // getter ÇÔ¼öµé
    inline string GetName() const { return data.name; }
    inline string GetElement() const { return data.element; }
    inline string GetSkillType() const { return data.type; }
    inline string GetAnimAction() const { return data.animAction; }
    inline int GetPower() const { return data.power; }
    inline int GetAccuracy() const { return data.accuracy; }
    inline const SkillData& GetSkillData() const { return data; }

    //virtual ~ISkill() = default;
};
