#include "CollisionManager.h"

HRESULT CollisionManager::Init()
{
	return E_NOTIMPL;
}

void CollisionManager::Release()
{
	ReleaseInstance();

}

//void CollisionManager::MissileCollisionCheck(IMissile* attacker, Minion* defender)
//{
//    if (attacker->GetState() == MissileState::MOVING && defender->GetIsAlive()) {
//        if (RectInRect(attacker->GetCollisionBox(), defender->GetCollisionBox()) && !defender->GetIsCollison()) {
//
//            attacker->SetState(MissileState::COLLIDED);
//            defender->SetImage("MinionDead");
//            defender->SetIsCollision(true);
//        };
//    }
//}