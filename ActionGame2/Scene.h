#pragma once

class Scene
{
public:
	Scene* nextScene = NULL;

	std::random_device rd;
	int curStage = 0;

	Player* player = NULL;
	Boss1* boss = NULL;

	std::vector<CEnemy*> enemyVec;

	ObjectManager obm;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	int GetRandomNum(int min, int max);
	D3DXVECTOR2 GetRandomVector(int xMin, int xMax, int yMin, int yMax);
};

