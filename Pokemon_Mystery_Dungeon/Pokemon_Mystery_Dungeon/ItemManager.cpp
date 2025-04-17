#include "ItemManager.h"

void ItemManager::SpawnRandomItem()
{
	//맵의 위치를 받아서 아이템 스폰
}

void ItemManager::GetItem(Player* player)
{
    for (auto it = items.begin(); it != items.end(); )
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
    }
}




void ItemManager::Update()
{

}

void ItemManager::Render()
{

}
