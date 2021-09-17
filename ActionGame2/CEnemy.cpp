#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = L"enemy";

	this->pos = pos;
	this->groundPos = pos.y;

	SetRigid(1);

	colorShader = new ColorShader();
	outlineShader = new OutlineShader();

	nowScene->obm.AddObject(ui = new EnemyUI(this));
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
	GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, groundPos) });

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1.0, 1.0, 1.0, 0.8f));
	else if (superArmor)
		outlineShader->Render(outlineShader, GetNowSprite(), ri, D3DXVECTOR4(1.0f, 0, 0, 1.0f));
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerbullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto pBullet = static_cast<Bullet*>(coli.obj);
		if (pBullet->type == Bullet::Type::SNIPER)
			if(!hit) nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pBullet->pos, D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(0.5, 0.5), 0.05f));
		Hit(pBullet->damage, pBullet->attackVector);
	}

}

void CEnemy::Hit(float damage, D3DXVECTOR2 addForce)
{
	if (hit) return;

	if (nowScene->player->powerUp)
		damage *= 1.3f;

	Unit::Hit(damage, addForce);

	if (nowScene->player->attackNum == -1)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandomVector(-70, 70, -100, 100), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(0.5, 0.5), 0.5f, true));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(5, 10)));
	}
	else if (nowScene->player->attackNum == 0)
	{
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2)));
	}
	else if (nowScene->player->attackNum == 2)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandomVector(-70, 70, -100, 100), D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 0.5f, true));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2)));
	}
	else
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2)));

	nowScene->player->PlusCombo(1);
}

void CEnemy::Attack(float deltaTime)
{
}

void CEnemy::CreateDetectRange(std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max, float detectGroundPos)
{
	nowScene->obm.AddObject(detectRange = new Range(this, targetName, addPos, min, max, D3DCOLOR_ARGB(255, 0, 0, 255), detectGroundPos));
}

void CEnemy::CreateAttackRange(std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max, float detectGroundPos)
{
	nowScene->obm.AddObject(attackRange = new Range(this, targetName, addPos, min, max, D3DCOLOR_ARGB(255, 255, 0, 0), detectGroundPos));
}

bool CEnemy::AttackColliderTarget()
{
	if (attackRange == NULL)
		return false;

	if (attackRange->bHit)
	{
		D3DXVECTOR2 disVec = attackRange->target->pos - pos;
		ri.scale.x = (disVec.x > 0) ? 1 : -1;

		attackRange->bHit = false;
		return true;
	}
	else
		return false;
}

bool CEnemy::DetectColliderTarget()
{
	if (detectRange == NULL)
		return false;

	if (detectRange->bHit)
	{
		detectRange->bHit = false;
		return true;
	}
	else
		return false;
}

bool CEnemy::Move(float deltaTime)
{
	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

	ri.scale.x = (dir.x > 0) ? 1 : -1;

	if (!DetectColliderTarget())
		return false;

	pos.x += dir.x * ability.speed * deltaTime;
	groundPos += dir.y * ability.speed / 2 * deltaTime;

	return true;
}

void CEnemy::Destroy()
{
	ui->destroy = true;
	attackRange->destroy = true;
	detectRange->destroy = true;
	nowScene->AddScore(nowScene->GetRandomNum(1000, 3000));

	nowScene->enemyManager.SortEnemy(this);

	destroy = true;
}

void CEnemy::SetState(CState<CEnemy>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}
