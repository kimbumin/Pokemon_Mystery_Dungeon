#include "SkillManager.h"
#include "EmberSkill.h"

void SkillManager::RegisterSkill(const string& name, shared_ptr<ISkill> skill)
{
	skill->Init();
	skillMap[name] = skill;
}

void SkillManager::Release()  
{  
   for (auto& [name, skill] : skillMap) {
       skill->Release();  
   }  
   skillMap.clear();  
}

shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
	auto it = skillMap.find(name);
	if (it != skillMap.end()) {
		return it->second->Clone();
	}
	return nullptr;
}

shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
	{
		auto it = skillMap.find(name);
		return (it != skillMap.end()) ? it->second : nullptr;
	}
}
