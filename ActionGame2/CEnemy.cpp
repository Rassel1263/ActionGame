#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = L"enemy";

	this->pos = pos;

	SetRigid(1);
	groundPos = -100;

	colorShader = new ColorShader();
}

void CEnemy::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1.0, 1.0, 1.0, 0.8f));
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerbullet")
	{
		auto pBullet = static_cast<Bullet*>(coli.obj);
		Hit(pBullet->damage, pBullet->attackVector);
	}
}

void CEnemy::Attack(float deltaTime)
{
}

bool CEnemy::Move(float deltaTime)
{

	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

	ri.scale.x = (dir.x > 0) ? 1 : -1;

	if (CheckRange(stopRange, GetDistanceFromTarget(nowScene->player->pos)))
		return false;

	pos += dir * ability.speed * deltaTime;

	return true;
}

void CEnemy::SetRange(float detectRange, float stopRange)
{
	this->detectionRange = detectRange;
	this->stopRange = stopRange;
}

bool CEnemy::CheckRange(float range, D3DXVECTOR2 distance)
{
	float length = distance.x * distance.x + distance.y * distance.y;

	return range * range >= length;
}


void CEnemy::SetState(CState<CEnemy>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}
