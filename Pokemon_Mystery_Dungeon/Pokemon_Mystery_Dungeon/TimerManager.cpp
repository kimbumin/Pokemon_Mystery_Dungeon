#include "TimerManager.h"
#include "Timer.h"

void TimerManager::Init()
{
	timer = new Timer();
	timer->Init();
}

void TimerManager::Release()
{
	timer->Release();
	delete timer;
	timer = nullptr;
}

void TimerManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimerManager::Render(HDC hdc)
{

}

float TimerManager::GetDeltaTime()
{
	if (timer)	return timer->GetDeltaTime();
	return 0.0f;
}
