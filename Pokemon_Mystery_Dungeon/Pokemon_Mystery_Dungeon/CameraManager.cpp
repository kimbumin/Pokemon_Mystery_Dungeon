#include "CameraManager.h"

void CameraManager::Init(int width, int height)
{
	screenHeight = width;
	screenWidth = height;
	SetCameraPos(0, 0);
}

void CameraManager::SetCameraPos(int x, int y)
{
	int halfWidth = screenWidth / 2;
	int halfHeight = screenHeight / 2;

	// 카메라의 위치를 설정
	viewRect.left = x - halfWidth;
	viewRect.top = y - halfHeight;
	viewRect.right = viewRect.left + screenWidth;
	viewRect.bottom = viewRect.top + screenHeight;

	// 카메라의 위치가 화면을 벗어나지 않도록 조정
	if (viewRect.left < 0) {
		viewRect.left = 0;
		viewRect.right = screenWidth;
	}
	if (viewRect.top < 0) {
		viewRect.top = 0;
		viewRect.bottom = screenHeight;
	}

	if (viewRect.right > TILEMAPTOOL_X) {
		viewRect.right = TILEMAPTOOL_X;
		viewRect.left = TILEMAPTOOL_X - screenWidth;
	}
	if (viewRect.bottom > TILEMAPTOOL_Y) {
		viewRect.bottom = TILEMAPTOOL_Y;
		viewRect.top = TILEMAPTOOL_Y - screenHeight;
	}
}
