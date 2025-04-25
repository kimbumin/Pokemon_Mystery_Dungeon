#pragma once

class UIElementText;
class PlayerInfoUIRenderer
{
public:
    static void SetBasicStats(UIElementText* nameText, UIElementText* levelText,
                              UIElementText* hpText);

    static void SetDetailedStats(UIElementText* atk, UIElementText* def,
                                 UIElementText* spAtk, UIElementText* spDef,
                                 UIElementText* speed, UIElementText* sum,
                                 UIElementText* avg, UIElementText* typeText);
};
