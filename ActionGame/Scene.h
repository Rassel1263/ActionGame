#pragma once
class Scene
{
public:
	ObjectManager obm;

	Player* player = NULL;
	Boss* boss = NULL;
	Scene* nextScene;

	
	bool spawnBoss = false;
	bool click = true;
	bool gameStop = false;

	static float score;

	int stage = 0;
	int wave = 3;

	float timer = 180;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void LoadAll();

	void GetScore(int score);
};

