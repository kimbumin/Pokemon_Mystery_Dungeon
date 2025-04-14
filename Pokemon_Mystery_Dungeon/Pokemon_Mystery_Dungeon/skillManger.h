#pragma once
#include <string>
using namespace std;

enum class SkillType
{
    Physical,
    Special,
    Status // 변화 기술
};

class skillManger
{
public:
    skillManger(string name, string description, SkillType type,
        int power, int accuracy, int maxPP);

    void Use();                     // 스킬 사용
    bool CanUse() const;            // PP가 남아 있는지 확인
    void ResetPP();                 // PP 초기화

    const std::string& GetName() const;
    const std::string& GetDescription() const;
    SkillType GetType() const;
    int GetPower() const;
    int GetAccuracy() const;
    int GetCurrentPP() const;
    int GetMaxPP() const;

private:
    string mName;
    string mDescription;
    SkillType mType;

    int mPower;     // 기술 위력
    int mAccuracy;  // 기술 명중률
    int mMaxPP;     // pp값
    int mCurrentPP;
};
