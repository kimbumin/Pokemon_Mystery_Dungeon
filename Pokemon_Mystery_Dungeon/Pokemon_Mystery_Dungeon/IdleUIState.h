#pragma once
#include "UIState.h"

static void DebugLog(const std::wstring& msg)
{
    OutputDebugStringW((msg + L"\n").c_str());
}

class IdleUIState : public UIState
{
public:
    IdleUIState() = default;
    ~IdleUIState() override = default;
    HRESULT Init() override
    {
        DebugLog(L"[DEBUG] IdleUIState::Init");
        return S_OK;
    };
    void Release() override {};
    void Update() override {};
    void Render(HDC hdc) override {};
};
