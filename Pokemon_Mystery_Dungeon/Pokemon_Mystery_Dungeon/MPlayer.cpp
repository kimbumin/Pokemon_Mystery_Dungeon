#include "MPlayer.h"
#include "Camera.h"

#include "KeyManager.h"
MPlayer::MPlayer() : pos{500, 300}, size{TILE_SIZE, TILE_SIZE}, speed(1)
{
    UpdateRect();
}

MPlayer::~MPlayer()
{
}

HRESULT MPlayer::Init()
{
    return S_OK;
}

void MPlayer::Release()
{
}

void MPlayer::Update()
{
    SavePrevPos();
    Move();
    UpdateRect();

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_OEM_PLUS))  // + Ű
        Camera::GetInstance()->ZoomIn();
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_OEM_MINUS))  // - Ű
        Camera::GetInstance()->ZoomOut();

    Camera::GetInstance()->SetCameraPos(pos);
}

void MPlayer::Render(HDC hdc)
{
    POINT camPos = Camera::GetInstance()->GetCameraPos();
    float zoom = Camera::GetInstance()->GetZoom();

    int left = static_cast<int>((rect.left - camPos.x) * zoom);
    int top = static_cast<int>((rect.top - camPos.y) * zoom);
    int right = static_cast<int>((rect.right - camPos.x) * zoom);
    int bottom = static_cast<int>((rect.bottom - camPos.y) * zoom);

    Rectangle(hdc, left, top, right, bottom);
}

void MPlayer::Move()
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
        pos.x -= speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
        pos.x += speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
        pos.y -= speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
        pos.y += speed;
}

void MPlayer::UpdateRect()
{
    rect.left = pos.x - size.cx / 2;
    rect.top = pos.y - size.cy / 2;
    rect.right = pos.x + size.cx / 2;
    rect.bottom = pos.y + size.cy / 2;
}
