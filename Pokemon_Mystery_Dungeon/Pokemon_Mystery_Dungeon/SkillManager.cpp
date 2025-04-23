#include "SkillManager.h"

#include "AttackSkill.h"
#include "EmberSkill.h"
#include "FireBlastSkill.h"
#include "StoneShowerSkill.h"
#include "SwingSkill.h"

void SkillManager::LoadSkillsFromCSV(const string& filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        OutputDebugStringA(
            ("Failed to open CSV file: " + filepath + "\n").c_str());
        return;
    }
    lineNumber = 0;
    while (getline(file, line))
    {
        lineNumber++;
        if (line.empty())
        {
            continue;
        }
        istringstream iss(line);
        try
        {
            getline(iss, token, ',');
            data.number = stoi(token);
            getline(iss, token, ',');
            data.name = token;
            getline(iss, token, ',');
            data.element = token;
            getline(iss, token, ',');
            data.type = token;
            getline(iss, token, ',');
            data.power = token.empty() ? 0 : stoi(token);
            getline(iss, token, ',');
            data.accuracy = token.empty() ? 0 : stoi(token);
            getline(iss, token, ',');
            data.pp = token.empty() ? 0 : stoi(token);

            if (data.name.empty())
                throw invalid_argument("Skill Name is empty");

            if (data.name == "Ember")
            {
                skill = make_shared<EmberSkill>(data);
            }
            else if (data.name == "FireBlast")
            {
                skill = make_shared<FireBlastSkill>(data);
            }
            else if (data.name == "StoneShower")
            {
                skill = make_shared<StoneShowerSkill>(data);
            }
            else if (data.power >= 70)
            {
                skill = make_shared<SwingSkill>(data);
            }
            else if (data.power < 70)
            {
                skill = make_shared<AttackSkill>(data);
            }
            skill->Init();
            skillMap[data.name] = skill;
            OutputDebugStringA(
                ("Registered Skill: " + data.name + "\n").c_str());
        }
        catch (const exception& e)
        {
            string errorMsg = "Error parsing CSV at line " +
                              to_string(lineNumber) + ": " + e.what() + "\n";
            OutputDebugStringA(errorMsg.c_str());
            continue;
        }
    }

    file.close();
}

shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end())
    {
        return it->second->Clone();
    }
    return nullptr;
}

shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
    auto it = skillMap.find(name);
    if (it != skillMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void SkillManager::Release()
{
    skillMap.clear();
}
