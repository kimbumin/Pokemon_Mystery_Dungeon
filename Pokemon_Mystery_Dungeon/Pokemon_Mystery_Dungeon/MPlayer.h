#pragma once
#include <Windows.h>

class MPlayer
{
private:
    POINT pos;      
    SIZE size;      
    RECT rect;      
    float speed;      
    POINT prevPos; // 이전 프레임 위치

public:
    MPlayer();
    ~MPlayer();

    HRESULT Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void Move(); // 방향키 입력 처리
    void UpdateRect(); // RECT 갱신
    void SavePrevPos() { prevPos = pos; }
    void UndoMove() { pos = prevPos; UpdateRect(); }

    RECT GetRect() const { return rect; }
    POINT GetPos() const { return pos; }
};
