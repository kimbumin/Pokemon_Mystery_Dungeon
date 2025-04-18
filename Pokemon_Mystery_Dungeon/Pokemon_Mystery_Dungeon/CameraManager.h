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

public:
	void Init(int width, int height);
	void SetCameraPos(int x, int y);

	RECT GetViewPos() const { return viewPos; }
	POINT GetCameraPos() const { return cameraPos; }

};

