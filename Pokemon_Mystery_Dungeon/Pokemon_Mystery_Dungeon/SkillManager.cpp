#include "SkillManager.h"

#include "AttackSkill.h"
#include "BoltSkill.h"
#include "EmberSkill.h"
#include "FireBlastSkill.h"
#include "StoneShowerSkill.h"
#include "SwingSkill.h"
#include "WaterGunSkill.h"

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
            continue;

        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ','))
            tokens.push_back(token);

        if (tokens.size() != 8)
        {
            OutputDebugStringA(("Invalid skill data at line " +
                                to_string(lineNumber) + ": " + line + "\n")
                                   .c_str());
            continue;
        }

        SkillData data;
        try
        {
            data.number = stoi(tokens[0]);
            data.name = tokens[1];
            data.element = tokens[2];
            data.type = tokens[3];
            data.power = stoi(tokens[4]);
            data.accuracy = stoi(tokens[5]);
            data.pp = stoi(tokens[6]);
            data.animType = tokens[7];

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
            else if (data.name == "Thunderbolt")
            {
                skill = make_shared<BoltSkill>(data);
            }
            else if (data.name == "WaterGun")
            {
                skill = make_shared<WaterGunSkill>(data);
            }
            else if (data.animType == "Swing")
            {
                skill = make_shared<SwingSkill>(data);
            }
            else if (data.animType == "Attack")
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
