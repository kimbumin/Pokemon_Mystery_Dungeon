#pragma once
#include "GameObject.h"
#include <functional>

enum class SkillType {  //기술타입 분류
    PHYSICAL,
    SPECIAL,
    STATUS
};

enum class SkillTarget {    //대상 타입 ex)플레이어->적
    ENEMY,
    PARTNER,
    PLAYER
};

class Unit; // 포켓몬 누구? 전방선언 바꿔도 됨 대충 끄적

class Skill : public GameObject 
{
private:
    string name;            //기술이름
    SkillType type;         //기술타입
    int power;              //기술위력
    int accuracy;           //명중률
    int maxPP;              //최대 pp
    int currentPP;          //사용한 pp
    SkillTarget targetType; //타겟이 뭔지
    string description;     //기술설명

    function<void(Unit* user, Unit* target)> effect; //기술의 실제 효과 함수

public:
    Skill();
    ~Skill();

    void Init(const string& name, SkillType type, int power, int accuracy, int maxPP,
        SkillTarget targetType, const string& description,
        function<void(Unit* user, Unit* target)> effect);

    void Update();
    void Render(HDC hdc);
    void Release();

    void Use(Unit* user, Unit* target); // 스킬 실행

    bool CanUse() const { return currentPP > 0; }   // pp가 있는지 확인 여부

    const string& GetName() const { return name; }
    const string& GetDescription() const { return description; }
    int GetCurrentPP() const { return currentPP; }
    int GetMaxPP() const { return maxPP; }
};
