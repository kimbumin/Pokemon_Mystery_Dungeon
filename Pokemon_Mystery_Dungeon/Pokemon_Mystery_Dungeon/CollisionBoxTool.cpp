#include "CollisionBoxTool.h"

#include <fstream>

#include "CommonFunction.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "Camera.h"

HRESULT CollisionBoxTool::Init(wstring mapName)
{
    isDragging = false;

    this->mapName = mapName;
    LoadFromFile();
    return S_OK;
}

void CollisionBoxTool::Release()
{
    boxes.clear();
}

void CollisionBoxTool::Update()
{
    POINT camPos = Camera::GetInstance()->GetCameraPos();
    POINT worldMousePos = {g_ptMouse.x + camPos.x, g_ptMouse.y + camPos.y};

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
    {
        isDragging = true;
        startPoint = worldMousePos;  // 월드 기준으로 저장
    }
    else if (KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
    {
        isDragging = false;

        RECT rect = {min(startPoint.x, worldMousePos.x),
                     min(startPoint.y, worldMousePos.y),
                     max(startPoint.x, worldMousePos.x),
                     max(startPoint.y, worldMousePos.y)};
        boxes.push_back({rect, L"Default"});
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
    {
        SaveToFile();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown('L'))
    {
        LoadFromFile();
    }
}

void CollisionBoxTool::Render(HDC hdc)
{
    POINT camPos = Camera::GetInstance()->GetCameraPos();

    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, brush);

    for (const auto& box : boxes)
    {
        Rectangle(hdc, box.rect.left - camPos.x, box.rect.top - camPos.y,
                  box.rect.right - camPos.x, box.rect.bottom - camPos.y);
    }

    if (isDragging)
    {
        POINT worldMousePos = {g_ptMouse.x + camPos.x, g_ptMouse.y + camPos.y};

        Rectangle(hdc, startPoint.x - camPos.x, startPoint.y - camPos.y,
                  worldMousePos.x - camPos.x, worldMousePos.y - camPos.y);
    }

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
}

void CollisionBoxTool::SaveToFile()
{
    if (mapName.empty())
    {
        MessageBox(g_hWnd, TEXT("Map 이름이 지정되지 않았습니다."),
                   TEXT("오류"), MB_OK);
        return;
    }

    std::wofstream file(mapName + L"_collisions.txt");
    if (!file.is_open())
    {
        MessageBox(g_hWnd, TEXT("파일 저장 실패"), TEXT("오류"), MB_OK);
        return;
    }

    for (auto& box : boxes)
    {
        file << box.rect.left << L" " << box.rect.top << L" " << box.rect.right
             << L" " << box.rect.bottom << L" " << box.tag << std::endl;
    }

    file.close();
    MessageBox(g_hWnd, TEXT("충돌박스가 성공적으로 저장되었습니다."),
               TEXT("완료"), MB_OK);
}

void CollisionBoxTool::LoadFromFile()
{
    if (mapName.empty())
    {
        MessageBox(g_hWnd, TEXT("Map 이름이 지정되지 않았습니다."),
                   TEXT("오류"), MB_OK);
        return;
    }

    boxes.clear();
    std::wifstream file(mapName + L"_collisions.txt");
    if (!file.is_open())
    {
        MessageBox(g_hWnd, TEXT("파일 로드 실패"), TEXT("오류"), MB_OK);
        return;
    }

    CollisionBox box;
    while (file >> box.rect.left >> box.rect.top >> box.rect.right >>
           box.rect.bottom >> box.tag)
    {
        boxes.push_back(box);
    }

    file.close();
    //   MessageBox(g_hWnd, TEXT("충돌박스가 성공적으로 로드되었습니다."),
    //   TEXT("완료"), MB_OK);
}

std::vector<RECT> CollisionBoxTool::GetRectBoxes() const
{
    std::vector<RECT> rectList;
    for (const auto& box : boxes)
    {
        rectList.push_back(box.rect);
    }
    return rectList;
}
