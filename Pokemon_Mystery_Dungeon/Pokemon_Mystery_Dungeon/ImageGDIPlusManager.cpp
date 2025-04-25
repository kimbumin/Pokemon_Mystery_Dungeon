#include "ImageGDIPlusManager.h"

#include "ImageGDIPlus.h"

void ImageGDIPlusManager::Init()
{
}

void ImageGDIPlusManager::Release()
{
    map<string, ImageGDIPlus*>::iterator iter;
    for (auto& pair : mapImages)
    {
        if (pair.second)
        {
            pair.second->Release();
            delete pair.second;
        }
    }
    mapImages.clear();

    ReleaseInstance();
}

ImageGDIPlus* ImageGDIPlusManager::AddImage(string key, const wchar_t* filePath,
                                            int maxFrameX, int maxFrameY,
                                            bool asGif)
{
    ImageGDIPlus* imageGDIPlus = nullptr;
    imageGDIPlus = FindImageGDIPlus(key);
    if (imageGDIPlus)
        return imageGDIPlus;

    imageGDIPlus = new ImageGDIPlus;
    if (FAILED(imageGDIPlus->Init(filePath, maxFrameX, maxFrameY, asGif)))
    {
        imageGDIPlus->Release();
        delete imageGDIPlus;

        return nullptr;
    }

    mapImages.insert(make_pair(key, imageGDIPlus));
    return imageGDIPlus;
}

void ImageGDIPlusManager::DeleteImageGDIPlus(string key)
{
    map<string, ImageGDIPlus*>::iterator iter = mapImages.find(key);

    if (iter == mapImages.end())
        return;

    (iter->second)->Release();
    delete iter->second;
    iter->second = nullptr;

    mapImages.erase(iter);
}

ImageGDIPlus* ImageGDIPlusManager::FindImageGDIPlus(string key)
{
    map<string, ImageGDIPlus*>::iterator iter = mapImages.find(key);

    if (iter == mapImages.end())
        return nullptr;

    return iter->second;
}
