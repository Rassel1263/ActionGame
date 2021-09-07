#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	this->pos = pos;
}

void CEnemy::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void CEnemy::Render()
{
	Unit::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerBullet")
	{
		if (!hit)
			Hit(static_cast<PlayerBullet*>(coli.obj)->damage);
	}
}

void CEnemy::SetState(CState<CEnemy>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);

}
