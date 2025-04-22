#pragma once
#include "Singleton.h"
#include "config.h"
#include <Windows.h>

class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;

private:
	RECT viewPos = { 0 };
	POINT cameraPos = { 0 };
	int screenWidth = 800;
	int screenHeight = 600;

	CameraManager() = default;
	int tileMapSizeX;
	int tileMapSizeY;

public:
	void Init(int camerWidth, int cameraHeight, int tileMapSizeX, int tileMapSizeY);
	void SetCameraPos(int x, int y);


	RECT GetViewPos() const { return viewPos; }
	POINT GetCameraPos() const { return cameraPos; }

};

