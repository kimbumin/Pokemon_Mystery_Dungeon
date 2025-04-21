#pragma once
#include "GameObject.h"
#include <vector>
#include <string>

struct CollisionBox
{
    RECT rect;
    std::wstring tag;
};

class CollisionBoxTool : public GameObject
{
private:
    std::vector<CollisionBox> boxes;
    POINT startPoint;
    bool isDragging;
    std::wstring mapName;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

    void SetMap(const std::wstring& name, Image* backgroundImage);
    const std::vector<CollisionBox>& GetCollisionBoxes() const { return boxes; }

private:
    void SaveToFile();
    void LoadFromFile();
};
