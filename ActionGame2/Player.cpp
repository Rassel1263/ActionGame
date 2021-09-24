#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	SetImages();

	hitTime = 0.1f;
	team = L"player";
	pos.y = -100;
	groundPos = -100;
	ability.SetAbility(100, 500);

	SetState(PlayerIdle::GetInstance());
	SetCollider(-60, 0, 60, 300, team);
	SetRigid(1);

	maxMp = 100;
	mp = 100;

	outlineShader = new OutlineShader();

	EnhanceData::GetInstance().GetData(skillEnhance);
	nowScene->obm.AddObject(new PlayerUI(this));

}

void Player::Update(float deltaTime)
{
	if (nowScene->bossIntro) return;

	if (fallowCamera)
	{
		if (pos.x > -1024 && pos.x < 16800)
			Camera::GetInstance().destCameraPos.x = pos.x;
	}

	if (ability.hp > 0)
	{
		CancelUpdate(deltaTime);
		UpdateItem(deltaTime);
		HealUpdate(deltaTime);

		if(skillEnhance[0])
			PlusMp(deltaTime * 3);
		Combo(deltaTime);
	}

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;

	GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, groundPos) });

	if (superArmor)
		outlineShader->Render(outlineShader, GetNowSprite(), ri, D3DXVECTOR4(1.0f, 0, 0, 1.0f));
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void Player::OnCollision(Collider& coli)
{
	if (coli.tag == L"enemybullet")
	{
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		auto eBullet = static_cast<Bullet*>(coli.obj);
		Hit(eBullet->damage, eBullet->attackVector);
	}
}

void Player::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"stay", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.03f);
	GetSprite(Images::JUMP).LoadAll(filePath + L"jump", 0.05f, false);
	GetSprite(Images::FALL).LoadAll(filePath + L"fall", 0.05f, false);
	GetSprite(Images::LANDING).LoadAll(filePath + L"landing", 0.05f, false);
	GetSprite(Images::SLIDE).LoadAll(filePath + L"slide", 0.03f, false);
	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.05f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"Stun", 0.05f, false);
	GetSprite(Images::STANDUP).LoadAll(filePath + L"StandUp", 0.05f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::JUMPATTACK1).LoadAll(filePath + L"jumpAttack1", 0.05f, false);
	GetSprite(Images::JUMPATTACK2).LoadAll(filePath + L"jumpAttack2", 0.05f, false);
	GetSprite(Images::JUMPATTACK3).LoadAll(filePath + L"jumpAttack3", 0.05f, false);

	GetSprite(Images::WEAKATTACK1).LoadAll(filePath + L"weakAttack1", 0.02f, false);
	GetSprite(Images::WEAKATTACK2).LoadAll(filePath + L"weakAttack2", 0.02f, false);
	GetSprite(Images::WEAKATTACK3).LoadAll(filePath + L"weakAttack3", 0.02f, false);
	GetSprite(Images::WEAKATTACK4).LoadAll(filePath + L"weakAttack4", 0.015f, false);
	GetSprite(Images::WEAKTATCKEND).LoadAll(filePath + L"weakAttackend", 0.1f, false);
	GetSprite(Images::STRONGATTACK).LoadAll(filePath + L"strongAttack", 0.05f, false);

	GetSprite(Images::GRENADE).LoadAll(filePath + L"grenade", 0.05f, false);

	GetSprite(Images::GUNKATA).LoadAll(filePath + L"Skillgunkata", 0.04f, false);
	GetSprite(Images::MOVESHOOT).LoadAll(filePath + L"SkillmoveShoot", 0.02f, false);
	GetSprite(Images::MACHINEGUN).LoadAll(filePath + L"Skillmachinegun", 0.03f, false);
	GetSprite(Images::SNIPER).LoadAll(filePath + L"Skillsniper", 0.05f, false);
	GetSprite(Images::NUCLEAR).LoadAll(filePath + L"Skillnuclear", 0.05f, false);


}

void Player::Hit(float damage, D3DXVECTOR2 addForce)
{
	if (ability.hp <= 0)
	{
		SetState(PlayerDie::GetInstance());
		return;
	}

	if (invincible || hit) return;


	nowScene->obm.AddObject(new Effect(L"Player/Hit3", pos + D3DXVECTOR2(nowScene->GetRandomNum(-50, 50), nowScene->GetRandomNum(100, 200)), D3DXVECTOR2(1.5, 1.5), D3DXVECTOR2(0.5, 0.5), 0.05f));
	Unit::Hit(damage, addForce);
}

void Player::SetState(CState<Player>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void Player::CreateAfterImage(int scene, float visibleTime, D3DXCOLOR color, bool fallow)
{
	if (visibleTime <= 0.0f)
	{
		Sprite spr = GetNowSprite();
		spr.scene = scene;
		nowScene->obm.AddObject(new AfterImage(spr, ri, D3DXVECTOR2(ri.scale.x * 2, 2), color, layer, fallow));
	}
	else
		nowScene->obm.AddObject(new AfterImage(GetNowSprite(), ri, visibleTime, color, layer));
}

void Player::PlusMp(float value)
{
	mp += value;

	mp = std::clamp(mp, 0.0f, maxMp);
}

void Player::PlusHp(float value)
{
	ability.hp += value;

	ability.hp = std::clamp(ability.hp, 0.0f, ability.maxHp);
}

void Player::PlusCombo(int value)
{
	comboInterval = 0.0f;
	prevCombo = combo;
	combo += value;

	if (combo > maxCombo)
		maxCombo = combo;
}

void Player::ItemEffective(int index)
{
	nowScene->obm.AddObject(new Effect(L"player/item", &pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(D3DXVECTOR2(0, 150)), 0.3f));

	switch (index)
	{
	case 1:
		powerUp = true;
		break;
	case 2:
		grenade = true;
		break;
	}
}

void Player::UpdateItem(float deltaTime)
{
	if (powerUp)
	{
		powerUpTimer += deltaTime;
		if (powerUpTimer >= 5.0f)
		{
			powerUp = false;
			powerUpTimer = 0.0f;
		}
	}
}

bool Player::Move(float deltaTime, bool moveShot)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (Input::GetInstance().KeyPress(VK_RIGHT))
		moveDir.x = 1;

	if (Input::GetInstance().KeyPress(VK_LEFT))
		moveDir.x = -1;

	if (Input::GetInstance().KeyPress(VK_UP))
		moveDir.y = 1;

	if (Input::GetInstance().KeyPress(VK_DOWN))
		moveDir.y = -1;

	if (moveDir.x != 0 && !moveShot)
		ri.scale.x = moveDir.x;

	if (moveDir == D3DXVECTOR2(0, 0))
		return false;

	if (pos.x + moveDir.x <= -1860)
		pos.x = -1859;

	if (pos.x + moveDir.x >= 23640)
		pos.x = 24639;

	int maxY = (nowScene->curStage == 1) ? 200 : -50;
	if (groundPos + moveDir.y >= maxY)
		groundPos = maxY;

	pos.x += moveDir.x * deltaTime * ability.speed;
	groundPos += moveDir.y * deltaTime * ability.speed / 2;

	return true;
}

void Player::CancelUpdate(float deltaTime)
{
	if (attackCancel)
	{
		cancelTimer -= deltaTime;

		if (cancelTimer <= 0.0f)
		{
			Game::GetInstance().timeScale = 1.0f;
			attackCancel = false;
		}
	}
}

void Player::HealUpdate(float deltaTime)
{
	if (healTimer < healTime)
		healTimer += deltaTime;

	if (Input::GetInstance().KeyDown('F'))
	{
		if (healTimer >= healTime)
		{
			SoundManager::GetInstance().Play(L"Heal");
			nowScene->obm.AddObject(new Effect(L"player/heal", &pos, D3DXVECTOR2(1.5, 1.5), D3DXVECTOR2(0, 150), 1.0f));
			PlusHp(10);
			healTimer = 0.0f;
		}
	}
}

void Player::Combo(float deltaTime)
{
	comboTimer += deltaTime;

	ComboInputCheck();
	ComboCheck();

	if (comboTimer > 0.2f)
	{
		comboTimer = 0.0f;
		comboInputs.clear();
	}

	comboInterval += deltaTime;

	if (comboInterval >= 0.5f)
	{
		combo = 0;
		comboInterval = 0.0f;
	}
}

void Player::ComboCheck()
{
	specialAttack = false;

	ComboChecking(1, 3, "RI", "RI", "X");
	ComboChecking(1, 3, "LE", "LE", "X");

	ComboChecking(2, 3, "RI", "LE", "X");
	ComboChecking(2, 3, "LE", "RI", "X");

	ComboChecking(3, 3, "DO", "RI", "X");
	ComboChecking(3, 3, "DO", "LE", "X");

	ComboChecking(4, 3, "LE", "LE", "S");
	ComboChecking(4, 3, "RI", "RI", "S");

	ComboChecking(5, 4, "RI", "DO", "LE", "X");
	ComboChecking(5, 4, "LE", "DO", "RI", "X");

	ComboChecking(6, 4, "DO", "DO", "UP", "S");

	if (specialAttack && !jumpAttack && !jump)
	{
		SetState(PlayerSpecialAttack::GetInstance());
		comboInputs.clear();
	}
}

void Player::ComboInputCheck()
{
	ComboInput(VK_LEFT, "LE");
	ComboInput(VK_RIGHT, "RI");
	ComboInput(VK_UP, "UP");
	ComboInput(VK_DOWN, "DO");
	ComboInput('X', "X");
	ComboInput('C', "C");
	ComboInput('S', "S");
}

void Player::ComboInput(unsigned char u, std::string name)
{
	if (Input::GetInstance().KeyDown(u))
	{
		comboInputs.push_back(name);
		comboTimer = 0.0f;
	}
}

void Player::ComboChecking(int skillNum, int inputAmount, ...)
{
	std::vector<std::string> ss;
	va_list ap;

	va_start(ap, inputAmount);
	for (int i = 0; i < inputAmount; i++)
	{
		ss.push_back(va_arg(ap, char*));
	}
	va_end(ap);

	int size = comboInputs.size();

	if (size >= inputAmount)
	{
		int count = 0;
		for (int i = 0; i < inputAmount; ++i)
		{
			if (comboInputs[size - i - 1] == ss[inputAmount - i - 1])
			{
				count++;
			}
		}

		if (count == inputAmount)
		{
			attackNum = skillNum;
			specialAttack = true;
		}
	}

}

void Player::CreateBullet(D3DXVECTOR2 offset, float speed, float damage, Bullet::Type type, bool jumpShot)
{
	offset.x *= ri.scale.x;

	if (type == Bullet::Type::BASIC)
	{
		Camera::GetInstance().cameraQuaken = { 3, 3 };

		if (jumpShot)
			nowScene->obm.AddObject(new Effect(L"Player/fire_jump", pos + offset, ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
		else
			nowScene->obm.AddObject(new Effect(L"Player/fire1", pos + offset, ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));

		SoundManager::GetInstance().Play(L"BasicShoot", false);
	}
	else if (type == Bullet::Type::AIRSHOT || type == Bullet::Type::MACHINEGUN || type == Bullet::Type::EMACHINEGUN)
	{
		Camera::GetInstance().cameraQuaken = { 5, 5 };
		nowScene->obm.AddObject(new Effect(L"Player/fire1", pos + offset, ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));

		SoundManager::GetInstance().Play(L"AirShoot", false);
	}
	else if (type == Bullet::Type::SNIPER || type == Bullet::Type::ESNIPER)
	{
		Camera::GetInstance().cameraQuaken = { 15, 15 };
		nowScene->obm.AddObject(new Effect(L"Player/fire_sniper", pos + offset, ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));

		SoundManager::GetInstance().Play(L"Sniper", false);
	}

	offset.y += 20;
	nowScene->obm.AddObject(new Bullet(team, pos + offset, D3DXVECTOR2(ri.scale.x, (jumpShot) ? -1 : 0), speed, damage, groundPos, type));
}

void Player::CreateAttackCollider(int scene, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 atkPower, float yVec, float time, bool fallow)
{
	if (GetNowSprite().scene == scene && !onAttack)
	{
		onAttack = true;
		Collider::AABB aabb = { min, max };
		if (fallow)
			nowScene->obm.AddObject(new AttackCollider(team, &pos, D3DXVECTOR2(offset.x * ri.scale.x, offset.y), aabb, damage, atkPower, yVec, time, groundPos));
		else
			nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(offset.x * ri.scale.x, offset.y), aabb, damage, atkPower, yVec, time, groundPos));
	}
}

void Player::SetSpecialAttack(Images image, int attackScene, float afterImageTime, float mp)
{
	if (this->mp < mp)
	{
		SetState(PlayerIdle::GetInstance());
		return;
	}

	this->mp -= mp;
	attackTimer = 0.0f;
	maxAttackTimer = 0.0f;

	SetAni(image);
	attackTimer = GetNowSprite().aniMaxtime * attackScene;

	if (image == Images::WEAKATTACK4)
	{
		SoundManager::GetInstance().Play(L"AirShootVoi");
	}
	else if (image == Images::SLIDE)
	{
		velocity.x += ri.scale.x * 3000;
		SoundManager::GetInstance().Play(L"Slide", false);
		SoundManager::GetInstance().Play(L"SlideVoi", false);
	}
	else if (image == Images::GUNKATA)
	{
		SoundManager::GetInstance().Play(L"GunKataVoi", false);
		nowScene->obm.AddObject(new SkillDirecting(attackTimer));

		if (skillEnhance[1]) // 스킬 1 강화 
		{
			nowScene->obm.AddObject(new Effect(L"Player/fire_gunkata2", pos + D3DXVECTOR2(0, 240), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.04f));
			nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 400) }, 8, D3DXVECTOR2(20, 0), 0.2f, attackTimer, groundPos));
		}
		else
		{
			nowScene->obm.AddObject(new Effect(L"Player/fire_gunkata", pos + D3DXVECTOR2(0, 240), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.04f));
			nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 400) }, 5, D3DXVECTOR2(20, 0), 0.2f, attackTimer, groundPos));
		}

		CreateAfterImage(0, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
	}
	else if (image == Images::MOVESHOOT)
	{
		SoundManager::GetInstance().Play(L"MoveShotVoi", false);

		maxAttackTimer = GetNowSprite().aniMaxtime * 2;
		CreateAfterImage(3, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
	}
	else if (image == Images::MACHINEGUN)
	{
		SoundManager::GetInstance().Play(L"MachineVoi", false);
		maxAttackTimer = GetNowSprite().aniMaxtime * 3;
		CreateAfterImage(0, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
	}

	else if (image == Images::SNIPER)
	{
		SoundManager::GetInstance().Play(L"SniperVoi", false);
		SoundManager::GetInstance().Play(L"SniperReady", false);

		for (auto& enemy : nowScene->enemyManager.enemyVec)
		{
			if (abs(enemy->groundPos - groundPos) <= 100)
			{
				if ((ri.scale.x >= 1) ? (enemy->pos.x > pos.x) : (enemy->pos.x < pos.x))
					nowScene->obm.AddObject(new Effect(L"Player/Sniper", &enemy->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 150), 0.3f));
			}
		}

		if (nowScene->boss)
		{
			if (abs(nowScene->boss->groundPos - groundPos) <= 100)
			{
				if ((ri.scale.x >= 1) ? (nowScene->boss->pos.x > pos.x) : (nowScene->boss->pos.x < pos.x))
					nowScene->obm.AddObject(new Effect(L"Player/Sniper", &nowScene->boss->pos, D3DXVECTOR2(1.5, 1.5), D3DXVECTOR2(0, 150), 0.3f));
			}
		}

		CreateAfterImage(0, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
		nowScene->obm.AddObject(new SkillDirecting(attackTimer));
	}
	else if (image == Images::NUCLEAR)
	{
		nuclear = true;
		nuclearTime = 1.0f;
		bCollider = false;
		nowScene->obm.AddObject(new SkillDirecting(0.0f, 1));
		nowScene->obm.AddObject(new Nuclear(D3DXVECTOR2(pos.x + 500 * ri.scale.x, pos.y)));
		CreateAfterImage(3, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));

		SoundManager::GetInstance().Play(L"NuclearVoi", false);
		SoundManager::GetInstance().Play(L"NuclearReady", false);
		SoundManager::GetInstance().Play(L"NuclearSound", false);
		SoundManager::GetInstance().Play(L"NuclearReady2", false);
	}

	nowScene->obm.AddObject(new Effect(L"Player/command", pos + D3DXVECTOR2(0, 300), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.5f, true));

	if (afterImageTime > 0.0f)
	{
		afterImage = true;
		this->afterImageTime = afterImageTime;
	}
}

void Player::SpecialAttackCancel()
{
	if (renderNum == IntEnum(Player::Images::GUNKATA))
	{
		nowScene->obm.AddObject(new Spectrum(GetNowSprite(), ri, 1.0f, D3DCOLOR_ARGB(200, 0, 0, 0), layer));
		CreateAfterImage(GetNowSprite().scene, 0.0f, D3DCOLOR_ARGB(125, 125, 225, 255), false);
		attackCancel = true;
	}
	else if (renderNum == IntEnum(Player::Images::MACHINEGUN))
	{
		nowScene->obm.AddObject(new Spectrum(GetNowSprite(), ri, 1.0f, D3DCOLOR_ARGB(200, 0, 0, 0), layer, attackTimer, maxAttackTimer, 4));
		CreateAfterImage(GetNowSprite().scene, 0.0f, D3DCOLOR_ARGB(125, 125, 225, 255), false);
		attackCancel = true;
	}
	else if (renderNum == IntEnum(Player::Images::SNIPER))
	{
		nowScene->obm.AddObject(new Spectrum(GetNowSprite(), ri, 1.0f, D3DCOLOR_ARGB(200, 0, 0, 0), layer, attackTimer, 99, 5));
		CreateAfterImage(GetNowSprite().scene, 0.0f, D3DCOLOR_ARGB(125, 125, 225, 255), false);
		attackCancel = true;
	}
	else if (renderNum == IntEnum(Player::Images::NUCLEAR))
	{
		nuclear = false;
		attackCancel = true;
		bCollider = true;
	}

	if (attackCancel)
	{
		Game::GetInstance().timeScale = 0.3f;
		cancelTimer = 0.2f;
	}
}
