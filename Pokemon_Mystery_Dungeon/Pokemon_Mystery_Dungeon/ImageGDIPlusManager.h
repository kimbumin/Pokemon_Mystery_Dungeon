#pragma once
#include "Singleton.h"
#include "config.h"

class ImageGDIPlus;
class ImageGDIPlusManager : public Singleton<ImageGDIPlusManager>
{
private:
	map<string, ImageGDIPlus*> mapImages;

public:
	void Init();
	void Release();

	ImageGDIPlus* AddImage(string key, const wchar_t* filePath, int maxFrameX = 1, int maxFrameY = 1);

	void DeleteImageGDIPlus(string key);
	ImageGDIPlus* FindImageGDIPlus(string key);
};

