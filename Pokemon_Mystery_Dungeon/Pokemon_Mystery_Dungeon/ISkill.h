#pragma once
#include "config.h"
#include "GameObject.h"

class ISkill : public GameObject {
public:
    virtual HRESULT Init() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;
    virtual void Use(GameObject* user, GameObject* target) = 0;
    virtual shared_ptr<ISkill> Clone() const = 0;


    virtual string GetName() const = 0;
    virtual string GetElement() const = 0;
    virtual string GetType() const = 0;
    virtual int GetPower() const = 0;
    virtual int GetAccuracy() const = 0;

    virtual ~ISkill() = default;
};
