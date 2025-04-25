#pragma once
#include "Image.h"
#include "ImageGDIPlus.h"
#include "UIElement.h"

class UIElementImage : public UIElement
{
private:
    ImageGDIPlus* imageGDIPlus = nullptr;
    Image* image = nullptr;

    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float alpha = 1.0f;
    float angle = 0.0f;

    bool flipX = false;
    bool flipY = false;

public:
    UIElementImage() = default;
    virtual ~UIElementImage() = default;

    void SetImage(ImageGDIPlus* img)
    {
        imageGDIPlus = img;
        image = nullptr;
    }
    void SetImage(Image* img)
    {
        image = img;
        imageGDIPlus = nullptr;
    }

    void setAlpha(float newAlpha)
    {
        alpha = newAlpha;
    }
    void setScale(float newScaleX, float newScaleY)
    {
        scaleX = newScaleX;
        scaleY = newScaleY;
    }
    void SetAngle(float newAngle)
    {
        angle = newAngle;
    }
    void SetFlip(bool newFlipX, bool newFlipY)
    {
        flipX = newFlipX;
        flipY = newFlipY;
    }
    int GetImageWidth() const
    {
        if (imageGDIPlus)
            return imageGDIPlus->GetWidth();
        if (image)
            return image->GetWidth();
        return 0;
    }

    int GetImageHeight() const
    {
        if (imageGDIPlus)
            return imageGDIPlus->GetHeight();
        if (image)
            return image->GetHeight();
        return 0;
    }

    void SetSpeed(float speed);

    void Render(HDC hdc) override;
    void Update() override;
    void Update(float dt) override;

    void RenderPartial(HDC hdc, int width, int height);
};
