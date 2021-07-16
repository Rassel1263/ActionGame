#pragma once
class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	
	int stage = 0;
	int wave = 3;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

