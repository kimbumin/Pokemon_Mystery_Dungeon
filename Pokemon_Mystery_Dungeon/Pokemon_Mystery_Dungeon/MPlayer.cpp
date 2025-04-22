#include "MPlayer.h"
#include "KeyManager.h"
MPlayer::MPlayer(): pos{ 500, 300 }, size{ TILE_SIZE, TILE_SIZE }, speed(1)
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
}

void MPlayer::Render(HDC hdc)
{
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void MPlayer::Move()
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))  pos.x -= speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)) pos.x += speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))    pos.y -= speed;
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))  pos.y += speed;
}

void MPlayer::UpdateRect()
{
    rect.left = pos.x - size.cx / 2;
    rect.top = pos.y - size.cy / 2;
    rect.right = pos.x + size.cx / 2;
    rect.bottom = pos.y + size.cy / 2;
}
