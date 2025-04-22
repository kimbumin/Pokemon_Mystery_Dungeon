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
    HRESULT Init(wstring mapName);
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;

    void SetMapName(const std::wstring& name) { mapName = name; }

    const std::vector<CollisionBox>& GetCollisionBoxes() const { return boxes; }
    std::vector<RECT> GetRectBoxes() const;

    void SaveToFile();
    void LoadFromFile();
};
