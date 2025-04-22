#pragma once
#include "Singleton.h"
// clang-format off
#include "config.h"
// clang-format on

class ImageGDIPlus;
class ImageGDIPlusManager : public Singleton<ImageGDIPlusManager>
{
private:
    map<string, ImageGDIPlus*> mapImages;

public:
    void Init();
    void Release();

    ImageGDIPlus* AddImage(string key, const wchar_t* filePath,
                           int maxFrameX = 1, int maxFrameY = 1,
                           bool asGif = false);

    void DeleteImageGDIPlus(string key);
    ImageGDIPlus* FindImageGDIPlus(string key);
};
