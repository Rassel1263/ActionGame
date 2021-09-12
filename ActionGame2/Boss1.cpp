#include "DXUT.h"
#include "Boss1.h"

Boss1::Boss1()
{
	team = L"enemy";
	ri.scale.x = -1;
	this->pos = D3DXVECTOR2(1500, 0);
	this->groundPos = pos.y;
	this->superArmor = true;

	hitTime = 0.1f;
	ability.SetAbility(1000, 100);
	SetImages();
	SetRigid(1);

	Camera::GetInstance().destCameraPos.x = pos.x;

	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 300), L"enemy");

	nowScene->obm.AddObject(detectRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-700, -400), D3DXVECTOR2(700, 400), D3DCOLOR_ARGB(255, 0, 0, 255)));
	nowScene->obm.AddObject(new BossUI(this));

	colorShader = new ColorShader();

	SetState(BossIdle::GetInstance());
	nowScene->obm.AddObject(new BossIntro());
}

void Boss1::Update(float deltaTime)
{
	UpdatePattern(deltaTime);

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void Boss1::Render()
{
	ri.pos = pos;
	GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, groundPos) });

	if (hit)
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1.0, 1.0, 1.0, 0.8f));
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void Boss1::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerbullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto pBullet = static_cast<Bullet*>(coli.obj);
		if (pBullet->type == Bullet::Type::SNIPER)
			if (!hit) nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pBullet->pos, D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(0.5, 0.5), 0.05f));
		Hit(pBullet->damage, pBullet->attackVector);
	}
}

void Boss1::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Boss/Type1/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK1).LoadAll(filePath + L"Attack1", 0.05f, false);
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
}

void Boss1::Hit(float damage, D3DXVECTOR2 addForce)
{
	if (hit) return;

	Unit::Hit(damage, addForce);

	if (nowScene->player->attackNum == 0)
	{
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(10, 15) * 0.1f));
	}
	else if (nowScene->player->attackNum == 2)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandomVector(-70, 70, -100, 100), D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 0.5f, true));
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2) * 0.1f));
	}
	else
		nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(3, 5) * 0.1f));

	nowScene->player->PlusCombo(1);
}

int Boss1::ChoosePattern()
{
	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

	if (abs(dir.y) > 0.2)
		return 2;
	else
		return 1;
}

void Boss1::UpdatePattern(float deltaTime)
{
	if (!nowScene->player->fallowCamera) return;

	if (pattern == 0)
	{
		restTime += deltaTime;

		if (restTime >= 0.5f)
		{
			restTime = 0.0f;
			pattern = ChoosePattern();
		}
	}
}

bool Boss1::Move(float deltaTime)
{
	D3DXVECTOR2 dir = { 0, 0 };
	D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

	if (!DetectColliderTarget())
		return false;

	ri.scale.x = (dir.x > 0) ? 1 : -1;
	pos.x += dir.x * 100 * deltaTime;
	groundPos += dir.y * 50 * deltaTime;

	return true;
}

bool Boss1::Pattern1(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 12 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Bullet(team, pos + D3DXVECTOR2(ri.scale.x * 50, 170), D3DXVECTOR2(ri.scale.x, 0), 1200, 10, groundPos, Bullet::Type::GOLDROCK));
	}

	return true;
}

bool Boss1::Pattern2(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 8 && !onAttack)
	{
		onAttack = true;

		D3DXVECTOR2 playerPos = D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->groundPos);
		auto lambda = [=] {
			nowScene->obm.AddObject(new AttackCollider(L"enemy", playerPos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200) }, 10, D3DXVECTOR2(0, 100), 0.1f, 0.05f, playerPos.y)); };

		nowScene->obm.AddObject(new Effect(L"enemy/magic", playerPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.1), 0.05f, 6, lambda));
	}

	return true;
}

bool Boss1::Pattern3(float deltaTime)
{
	return false;
}


bool Boss1::DetectColliderTarget()
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

void Boss1::SetState(CState<Boss1>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void Boss1::ResetPattern()
{
	pattern = 0;
	onAttack = false;
}
