#include "DXUT.h"
#include "Nuclear.h"

Nuclear::Nuclear(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/effect/Player/nuclear", 0.02f, false);
	ri.pivot = { 0.5 ,0.2 };
	this->pos = pos;
}

void Nuclear::Update(float deltaTime)
{
	this->groundPos = pos.y;
	layer = 1080 - (groundPos + 540);

	if (nowScene->player->nuclear)
	{

		if (Input::GetInstance().KeyPress(VK_RIGHT))
			pos.x += deltaTime * 500;

		if (Input::GetInstance().KeyPress(VK_LEFT))
			pos.x -= deltaTime * 500;

		if (Input::GetInstance().KeyPress(VK_UP))
			pos.y += deltaTime * 500;

		if (Input::GetInstance().KeyPress(VK_DOWN))
			pos.y -= deltaTime * 500;
	}

	if (spr.scene > 37 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new SkillDirecting(1.0f, 2));
		Camera::GetInstance().cameraQuaken = { 50, 50};
		nowScene->obm.AddObject(new AttackCollider(L"player", pos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-500, 0), D3DXVECTOR2(500, 300) }, 100, D3DXVECTOR2(0, 0), 0.0f, 0.1f, groundPos));
		SoundManager::GetInstance().Stop(L"NuclearFall");
		SoundManager::GetInstance().Play(L"NuclearBoom", false);
	}

	if (!nowScene->player->nuclear)
		spr.Update(deltaTime);

	if (!spr.bAnimation)
		destroy = true;

}

void Nuclear::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
