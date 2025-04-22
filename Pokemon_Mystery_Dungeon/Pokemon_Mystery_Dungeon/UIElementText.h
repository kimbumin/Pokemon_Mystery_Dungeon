#pragma once
#include "UIElement.h"
#include <gdiplus.h>
#include <string>
#include <map>

#pragma comment(lib, "gdiplus.lib")

class UIElementText : public UIElement
{
private:
	std::wstring text;
	std::wstring fontName = L"Arial";
	int fontSize = 20;
	float textLine = 3.0f;

	Gdiplus::Color textColor = Gdiplus::Color(255, 0x1C, 0x1C, 0x84); // #1C1C84

public:
	UIElementText() = default;
	virtual ~UIElementText() = default;

	void Render(HDC hdc) override;
	void RenderDialogue(const std::wstring& txt, const std::map<std::wstring, std::wstring>& values);


	void DrawColoredText(Gdiplus::Graphics& graphics, const std::wstring& line, float x, float y);

	void SetText(const std::wstring& txt) { text = txt; }
	void SetTextLine(float line) { textLine = line; }
	void SetFont(const std::wstring& font, int size)
	{
		fontName = font;
		fontSize = size;
	}
	void SetTextColor(int r, int g, int b, int a)
	{
		textColor = Gdiplus::Color(a, r, g, b);
	}
};
