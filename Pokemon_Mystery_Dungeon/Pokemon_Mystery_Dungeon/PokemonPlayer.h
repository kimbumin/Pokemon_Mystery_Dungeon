#pragma once
#include "PokemonBase.h"

class Item;
class PokemonPlayer : public PokemonBase
{
private:
 
    // 아이템 인벤토리
    // vector<Item*> inventory;

    int exp = 0;
    int expToLevelUp;
    // int inventorySize = 20;
protected:

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    // 아이템 관련 행동 처리
    bool CanPickUpItem() const;
    void PickUpItem(Item* item);
    void AddItemToBag(Item* item);
    void UseItem(Item* item);

    // 레벨 관련
    void GainExp(int amount);
    void LevelUp();
};

