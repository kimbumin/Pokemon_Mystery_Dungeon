#pragma once
#include "Config.h"

// UI 공통 인터페이스
class UIState
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) {}
	virtual ~UIState() {};
};

/*
* 
  UIManager로 상테 전환을 관리하는 클래스

* UIState 상속 클래스
    [만든거]
	타이틀 화면 전체		TitleUIState
	인벤토리 창				InventoryUIState
	스킬 정보 창			SkillInfoUIState
	스킬 선택 창			SkillSelectUIState


	[아직 안만듬]
	상태 창 				StatusUIState
	상태이상 상세 정보 창	StatusEffectInfoUIState
	대화창 					DialogueUIState
*/