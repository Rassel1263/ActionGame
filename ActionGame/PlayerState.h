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

class PlayerBind : public CState<Player>
{
public:
	static PlayerBind* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerHit : public CState<Player>
{
public:
	static PlayerHit* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};

class PlayerDie : public CState<Player>
{
public:
	static PlayerDie* instance;

	virtual void EnterState(Player* obj);
	virtual void UpdateState(Player* obj, float deltaTime);
	virtual void ExitState(Player* obj);
};