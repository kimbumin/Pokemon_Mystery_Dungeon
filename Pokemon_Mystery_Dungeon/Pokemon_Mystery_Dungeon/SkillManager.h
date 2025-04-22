#pragma once
#include "GameObject.h"
#include "ISkill.h"

class SkillManager : public GameObject
{
private:
    unordered_map<string, shared_ptr<ISkill>> skillMap;

public:
    void RegisterSkill(const string& name, shared_ptr<ISkill> skill);
    void Release();

    shared_ptr<ISkill> CreateSkill(const string& name);
    shared_ptr<ISkill> FindSkill(const string& name);
};
