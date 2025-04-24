#include "PlayerInfoUIRender.h"
#include "UIElementText.h"
#include "PlayerManager.h"
#include "PokemonPlayer.h"
#include "CommonFunction.h"
#include <string>

void PlayerInfoUIRenderer::SetBasicStats(UIElementText* nameText,
                                         UIElementText* levelText,
                                         UIElementText* hpText)
{
    auto* player = PlayerManager::GetInstance()->GetPlayer();
    if (!player)
        return;

    const PokemonData& data = player->GetCurrentPokemonData();
    int currentHp = player->GetCurrentHp();
    int level = player->GetLevel();

    if (nameText)
        nameText->SetText(ToWString(data.name));

    if (levelText)
        levelText->SetText(L"Lv. " + std::to_wstring(level));

    if (hpText)
        hpText->SetText(L"HP " + std::to_wstring(currentHp) + L" / " +
                        std::to_wstring(data.hp));
}

void PlayerInfoUIRenderer::SetDetailedStats(
    UIElementText* atk, UIElementText* def, UIElementText* spAtk,
    UIElementText* spDef, UIElementText* speed, UIElementText* sum,
    UIElementText* avg, UIElementText* typeText)
{
    auto* player = PlayerManager::GetInstance()->GetPlayer();
    if (!player)
        return;

    const PokemonData& data = player->GetCurrentPokemonData();

    if (atk)
        atk->SetText(L"ATK: " + std::to_wstring(data.atk));
    if (def)
        def->SetText(L"DEF: " + std::to_wstring(data.def));
    if (spAtk)
        spAtk->SetText(L"SpATK: " + std::to_wstring(data.spAtk));
    if (spDef)
        spDef->SetText(L"SpDEF: " + std::to_wstring(data.spDef));
    if (speed)
        speed->SetText(L"SPD: " + std::to_wstring(data.speed));
    if (sum)
        sum->SetText(L"SUM: " + std::to_wstring(data.sum));
    if (avg)
        avg->SetText(L"AVG: " + std::to_wstring(data.average));

    if (typeText)
    {
        std::wstring types;
        for (const std::string& type : data.types)
        {
            types += ToWString(type) + L" ";
        }
        typeText->SetText(L"TYPE: " + types);
    }
}
