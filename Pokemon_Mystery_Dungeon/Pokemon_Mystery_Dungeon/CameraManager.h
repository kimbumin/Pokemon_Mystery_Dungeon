#pragma once
#include "Singleton.h"
#include "config.h"
#include <Windows.h>

class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;

private:
	RECT viewRect = { 0 };
	int screenWidth = 800;
	int screenHeight = 600;

	CameraManager() = default;

public:
	void Init(int width, int height);
	void SetCameraPos(int x, int y);

	RECT GetCameraRect() const { return viewRect; }

};

