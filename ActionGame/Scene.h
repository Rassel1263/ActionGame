#pragma once
class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

