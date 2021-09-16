#pragma once

class Scene
{
public:
	Scene* nextScene = NULL;

	static float score;
	float destScore = 0.0f;

	bool stopTime = false;
	bool spawnBoss = false;
	bool bossIntro = false;
	bool timeOver = false;
	float gameTime = 180.0f;

	std::random_device rd;
	int curStage = 0;

	Player* player = NULL;
	CBoss* boss = NULL;
	EnemyManager enemyManager;

	ObjectManager obm;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	void LoadFiles();

	int GetRandomNum(int min, int max);
	D3DXVECTOR2 GetRandomVector(int xMin, int xMax, int yMin, int yMax);
	void AddScore(float value);
};

