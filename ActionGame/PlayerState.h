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

