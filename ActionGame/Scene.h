#pragma once
class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	
	bool spawnBoss = false;

	int stage = 0;
	int wave = 3;

	float timer = 180;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

