#pragma once

class PlayerIdle : public CState<Player>
{
public:
	static PlayerIdle* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerDown : public CState<Player>
{
public:
	static PlayerDown* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerWalk : public CState<Player>
{
public:
	float eftTimer = 0.0f;

	static PlayerWalk* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerJump : public CState<Player>
{
public:

	static PlayerJump* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};


class PlayerFall : public CState<Player>
{
public:
	static PlayerFall* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerLAttack : public CState<Player>
{
public:
	static PlayerLAttack* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerHAttack : public CState<Player>
{
public:
	static PlayerHAttack* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerLSAttack : public CState<Player>
{
public:
	static PlayerLSAttack* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};


class PlayerHSAttack : public CState<Player>
{
public:
	static PlayerHSAttack* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};