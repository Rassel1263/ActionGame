#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	SetImages();

	groundPos = -100;
	ability.SetAbility(100, 50);

	SetState(PlayerIdle::GetInstance());
	SetCollider(-60, 0, 60, 300, L"player");
	SetRigid(1);
}

void Player::Update(float deltaTime)
{
	Camera::GetInstance().destCameraPos.x = pos.x + 600 * ri.scale.x;

	Combo(deltaTime);

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void Player::Render()
{
	GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, groundPos) });
	Unit::Render();
}

void Player::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"stay", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::JUMP).LoadAll(filePath + L"jump", 0.05f, false);
	GetSprite(Images::FALL).LoadAll(filePath + L"fall", 0.05f, false);
	GetSprite(Images::LANDING).LoadAll(filePath + L"landing", 0.05f, false);
	GetSprite(Images::SLIDE).LoadAll(filePath + L"slide", 0.05f, false);
	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/Player/shadow");

	GetSprite(Images::WEAKATTACK1).LoadAll(filePath + L"weakAttack1", 0.05f, false);
	GetSprite(Images::WEAKATTACK2).LoadAll(filePath + L"weakAttack2", 0.05f, false);
	GetSprite(Images::WEAKATTACK3).LoadAll(filePath + L"weakAttack3", 0.05f, false);
	GetSprite(Images::WEAKATTACK4).LoadAll(filePath + L"weakAttack4", 0.05f, false);
	GetSprite(Images::WEAKTATCKEND).LoadAll(filePath + L"weakAttackend", 0.05f, false);

	GetSprite(Images::GUNKATA).LoadAll(filePath + L"Skillgunkata", 0.04f, false);
	GetSprite(Images::MOVESHOOT).LoadAll(filePath + L"SkillmoveShoot", 0.02f, false);
}

void Player::SetState(CState<Player>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void Player::CreateAfterImage(int scene, float visibleTime, D3DXCOLOR color)
{
	if (visibleTime <= 0.0f)
	{
		Sprite spr = GetNowSprite();
		spr.scene = scene;
		nowScene->obm.AddObject(new AfterImage(spr, ri, D3DXVECTOR2(ri.scale.x * 2, 2), color));
	}
	else
		nowScene->obm.AddObject(new AfterImage(GetNowSprite(), ri, visibleTime, color));
}

bool Player::Move(float deltaTime)
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

	if (moveDir.x != 0)
		ri.scale.x = moveDir.x;
	if (moveDir == D3DXVECTOR2(0, 0))
		return false;

	pos.x += moveDir.x * deltaTime * 500;
	groundPos += moveDir.y * deltaTime * 250;

	return true;
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


	if (specialAttack)
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
