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
		// 임시: 스킬 클래스마다 복사 생성자 필요
		return make_shared<EmberSkill>(*dynamic_cast<EmberSkill*>(it->second.get()));
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
