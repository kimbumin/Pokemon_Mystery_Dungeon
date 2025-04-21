#include "CollisionBoxTool.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "CommonFunction.h"
#include <fstream>

HRESULT CollisionBoxTool::Init()
{
    isDragging = false;
    return S_OK;
}

void CollisionBoxTool::Release()
{
    boxes.clear();
}

void CollisionBoxTool::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
    {
        isDragging = true;
        startPoint = g_ptMouse;
    }
    else if (KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
    {
        isDragging = false;
        RECT rect = {
            min(startPoint.x, g_ptMouse.x),
            min(startPoint.y, g_ptMouse.y),
            max(startPoint.x, g_ptMouse.x),
            max(startPoint.y, g_ptMouse.y)
        };

        boxes.push_back({ rect, L"Default" });
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown('S')) {
        SaveToFile();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown('L')) {
        LoadFromFile();
    }
}

void CollisionBoxTool::Render(HDC hdc)
{

    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, brush);

    for (const auto& box : boxes)
    {
        Rectangle(hdc, box.rect.left, box.rect.top, box.rect.right, box.rect.bottom);
    }

    if (isDragging)
    {
        Rectangle(hdc, startPoint.x, startPoint.y, g_ptMouse.x, g_ptMouse.y);
    }

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
}

void CollisionBoxTool::SaveToFile()
{
    std::wofstream file(mapName + L"_collisions.txt");
    for (auto& box : boxes)
    {
        file << box.rect.left << L" " << box.rect.top << L" "
            << box.rect.right << L" " << box.rect.bottom << L" "
            << box.tag << std::endl;
    }
    file.close();
    MessageBox(g_hWnd, TEXT("충돌박스가 성공적으로 저장되었습니다."), TEXT("완료"), MB_OK);

}

void CollisionBoxTool::LoadFromFile()
{
    boxes.clear();
    std::wifstream file(mapName + L"_collisions.txt");
    CollisionBox box;
    while (file >> box.rect.left >> box.rect.top >> box.rect.right >> box.rect.bottom >> box.tag)
    {
        boxes.push_back(box);
    }
    file.close();
    MessageBox(g_hWnd, TEXT("충돌박스가 성공적으로 로드되었습니다."), TEXT("완료"), MB_OK);
}
