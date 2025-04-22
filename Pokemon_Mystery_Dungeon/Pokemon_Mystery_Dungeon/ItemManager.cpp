#include "ItemManager.h"

#include "LeppaBerry.h"
#include "OranBerry.h"

void ItemManager::SpawnRandomItem()
{
    int randX = 200;
    int randY = 200;

    int randomItem = rand() % 2;

    unique_ptr<IItem> newItem;

    // 팩토리로 바꿀 수 있음
    switch (randomItem)
    {
        case 0:
            newItem = make_unique<LeppaBerry>();
            break;
        case 1:
            newItem = make_unique<OranBerry>();
            break;
    }

    if (newItem)
    {
        newItem->Init();
        newItem->SetPosition(randX, randY);
        items.push_back(move(newItem));
    }
}

void ItemManager::GetItem(/*Player* player*/)
{
    /*for (auto it = items.begin(); it != items.end(); )
    {
        POINT playerPos = player->GetPosition();
        IItem* item = it->get(); // IItem 꺼내기

        if (playerPos.x == item->GetX() && playerPos.y == item->GetY())
        {
            std::string itemName = item->GetName();

            player->AddItem(itemName); // 이름 기반으로 추가

            it = items.erase(it); // unique_ptr 자동 삭제됨
        }
        else
        {
            ++it;
        }
    }*/
}

void ItemManager::Update()
{
    for (auto& item : items)
    {
        item->Update();
    }
}

void ItemManager::Render(HDC hdc)
{
    for (auto& item : items)
    {
        item->Render(hdc);
    }
}
