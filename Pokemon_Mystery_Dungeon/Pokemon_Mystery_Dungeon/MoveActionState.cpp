#include "MoveActionState.h"
#include "PokemonBase.h"
#include "CommonFunction.h"

void MoveActionState::Enter(PokemonBase* owner)
{
	isFinished = false;
	currentPos = owner->GetPos();
	startPos = currentPos;
	destPos = startPos;

	direction = owner->GetDirection();
	auto [dx, dy] = directionOffsets[static_cast<int>(direction)];
	destPos.x += dx * TILE_SIZE;
	destPos.y += dy * TILE_SIZE;
	
	duration = 1.f; 
	// Check 애니메이션 총 재생 시간 -> 하드코딩 말고 다른 방법 개선 필요 
	// (PokemonBase에서도 AddAnimation 할때 하드 코딩 되어있음)
	elapsed = 0.f;

	owner->PlayWalkAnim();
}

void MoveActionState::Update(PokemonBase* owner)
{
	if (isFinished)
	{
		return;
	}

	elapsed += TimerManager::GetInstance()->GetDeltaTime();

	if (elapsed >= duration)
	{
		currentPos = destPos;
		owner->SetPos(currentPos);
		isFinished = true;
		return;
	}

	float t = elapsed / duration;
	
	currentPos.x = Lerp(startPos.x, destPos.x, t);
	currentPos.y = Lerp(startPos.y, destPos.y, t);
	owner->SetPos(currentPos);
}

void MoveActionState::Exit(PokemonBase* owner)
{

}

bool MoveActionState::IsFinished()
{
	return isFinished;
}

bool MoveActionState::CanOverride()
{
	return isFinished;
}

float MoveActionState::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

MoveActionState::MoveActionState()
{
	isFinished = false;
}
