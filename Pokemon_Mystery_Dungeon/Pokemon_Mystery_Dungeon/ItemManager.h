#include"IItem.h"

class ItemManager
{
private:
    vector<unique_ptr<IItem>> items;

public:

    void SpawnRandomItem(); // 랜덤 아이템 생성
    void GetItem(/*Player* player*/);// 플레이어의 위치와 충돌 검사 후 플레이어가 습득
    void Update();
    void Render(HDC hdc); //맵에 아이템 랜더
};
