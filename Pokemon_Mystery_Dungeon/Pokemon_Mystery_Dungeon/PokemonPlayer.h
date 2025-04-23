#pragma once
#include "PokemonBase.h"

class Item;
class ISkill;
class PokemonPlayer : public PokemonBase
{
private:
    // 아이템 인벤토리
    // vector<Item*> inventory;

    int exp = 0;
    int expToLevelUp;
    // int inventorySize = 20;
    
    // SquareScene 관련
    bool isInSquare = false;
    SIZE size = {TILE_SIZE, TILE_SIZE};
    RECT rect;
    float speed = 1;
    POINT prevPos = POINT{static_cast<int>(pos.x),
                          static_cast<int>(pos.y)};  // 이전 프레임 위치
    

protected:
public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    // SquareScene 관련
    void SquareModeMove();
    void UpdateRect();
    void SavePrevPos()
    {
        prevPos = POINT{static_cast<int>(pos.x), static_cast<int>(pos.y)};
    }
    void UndoMove()
    {
        pos = FPOINT{static_cast<float>(prevPos.x), static_cast<float>(prevPos.y)};
        UpdateRect();
    }

    RECT GetRect() const
    {
        return rect;
    }
    void IsInSquare(bool isFree)
    {
        isInSquare = isFree;
    }

    // 아이템 관련 행동 처리
    bool CanPickUpItem() const;
    void PickUpItem(Item* item);
    void AddItemToBag(Item* item);
    void UseItem(Item* item);

    // 레벨 관련
    void GainExp(int amount);
    void LevelUp();
    void PrintLevelUpSummaryDialogue(const PokemonData& prevStatus,
                                     const PokemonData& newStatus);

    // 진화 관련
    void TryEvolve();
    void EvolveTo(int newPokemonId);

};
