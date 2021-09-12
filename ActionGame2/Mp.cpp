#include "DXUT.h"
#include "Mp.h"

Mp::Mp(D3DXVECTOR2 pos, float startAngle, float amount)
{
	this->pos = pos;
	this->amount = amount;

	spr.LoadAll(L"Assets/Sprites/effect/Player/mp.png");

	this->turnSpeed = D3DXToRadian(10);
	startTime = 1.0f;
	this->angle = D3DXToRadian(startAngle);

	CreateCollider(D3DXVECTOR2(-5, -5), D3DXVECTOR2(5, 5), L"mp");

	layer = 1090;
}

void Mp::Update(float deltaTime)
{
	if (startTime < 0.0f)
		startTime -= deltaTime;
	else
	{
		D3DXVECTOR2 distance = nowScene->player->pos + D3DXVECTOR2(0, 150) - pos;
		float targetAngle = atan2(distance.y, distance.x);
		float diff = targetAngle - angle;

		turnTime += deltaTime;

		if (turnTime >= 0.01f)
		{
			if (diff > D3DX_PI)
				diff -= D3DX_PI * 2;
			else if (diff < -D3DX_PI)
				diff += D3DX_PI * 2;

			if (diff > turnSpeed)
				angle += turnSpeed;
			else if (diff < -turnSpeed)
				angle -= turnSpeed;
			else
				angle = targetAngle;


			turnTime = 0.0f;
		}
	}

	pos += D3DXVECTOR2(cos(angle), sinf(angle)) * 1000 * deltaTime;
}

void Mp::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Mp::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
	{
		nowScene->player->PlusMp(amount);
		destroy = true;
	}
}
