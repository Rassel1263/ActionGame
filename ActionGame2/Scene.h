#pragma once

class Scene
{
public:
	Scene* nextScene = NULL;

	std::random_device rd;
	int curStage = 0;

	Player* player = NULL;

	ObjectManager obm;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	int GetRandomNum(int min, int max);
};

