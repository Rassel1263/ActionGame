#pragma once

class EnemyIdle : public CState<Enemy>
{
public:
	static EnemyIdle* instance;

	virtual void EnterState(Enemy* obj);
	virtual void UpdateState(Enemy* obj, float deltaTime);
	virtual void ExitState(Enemy* obj);
};

class EnemyWalk : public CState<Enemy>
{
public:
	static EnemyWalk* instance;

	virtual void EnterState(Enemy* obj);
	virtual void UpdateState(Enemy* obj, float deltaTime);
	virtual void ExitState(Enemy* obj);
};

class EnemyAttack : public CState<Enemy>
{
public:
	static EnemyAttack* instance;

	virtual void EnterState(Enemy* obj);
	virtual void UpdateState(Enemy* obj, float deltaTime);
	virtual void ExitState(Enemy* obj);
};

class EnemyHit : public CState<Enemy>
{
public:
	static EnemyHit* instance;

	virtual void EnterState(Enemy* obj);
	virtual void UpdateState(Enemy* obj, float deltaTime);
	virtual void ExitState(Enemy* obj);
};