#include "CameraManager.h"

void CameraManager::Init(int camerWidth, int cameraHeight, int mapSizeX, int mapSizeY)
{
	screenWidth = camerWidth;
	screenHeight = cameraHeight;

	tileMapSizeX = mapSizeX;
	tileMapSizeY = mapSizeY;
	SetCameraPos(0, 0);
}

void CameraManager::SetCameraPos(int x, int y)
{
	// 카메라 위치 설정
	cameraPos.x = x;
	cameraPos.y = y;

	int halfWidth = screenWidth / 2;
	int halfHeight = screenHeight / 2;

	// 카메라 위치를 기준으로 view 영역 설정
	viewPos.left = x - halfWidth;
	viewPos.top = y - halfHeight;
	viewPos.right = viewPos.left + screenWidth;
	viewPos.bottom = viewPos.top + screenHeight;

	// 카메라의 위치가 화면을 벗어나지 않도록 조정
	if (viewPos.left < 0) {
		viewPos.left = 0;
		viewPos.right = screenWidth;
		cameraPos.x = screenWidth / 2;
	}
	if (viewPos.top < 0) {
		viewPos.top = 0;
		viewPos.bottom = screenHeight;
		cameraPos.y = screenHeight / 2;
	}

	if (viewPos.right > tileMapSizeX) {
		viewPos.right = tileMapSizeX;
		viewPos.left = tileMapSizeX - screenWidth;
		cameraPos.x = tileMapSizeX - screenWidth / 2;
	}
	if (viewPos.bottom > tileMapSizeY) {
		viewPos.bottom = tileMapSizeY;
		viewPos.top = tileMapSizeY - screenHeight;
		cameraPos.y = tileMapSizeY - screenHeight / 2;
	}
}
