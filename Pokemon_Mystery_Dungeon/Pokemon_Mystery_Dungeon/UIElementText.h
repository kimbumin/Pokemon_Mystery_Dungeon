#pragma once
// clang-format off
#include "UIElement.h"
// clang-format on

#include <gdiplus.h>

#include <map>
#include <string>

#pragma comment(lib, "gdiplus.lib")

class UIElementText : public UIElement
{
private:
    std::wstring text;
    std::wstring fontName = L"DungGeunMo";
    int fontSize = 20;
    float textLine = 3.0f;

    COLORREF textColor = RGB(0x1C, 0x1C, 0x84);

    wstring fullText;
    int visibleTextLength = 0;
    float elapsedTime = 0.0f;
    float charInterval = 0.05f;
    bool isTyping = false;

public:
    UIElementText() = default;
    virtual ~UIElementText() = default;

    void Render(HDC hdc) override;
    const std::wstring& RenderDialogue(
        const std::wstring& txt,
        const std::map<std::wstring, std::wstring>& values);
    void DrawColoredText(HDC hdc, const std::wstring& line,
                         float x, float y);

    void SetText(const std::wstring& txt);
    void SetTextLine(float line);
    void SetFont(int size);
    void SetTextColorRGB(int r, int g, int b);
    void TypeEffect(const wstring& txt, float interval = 0.05f);
    void SkipTyping();
    void Update(float dt);
};
