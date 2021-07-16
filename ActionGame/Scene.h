#pragma once
class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	
	int stage = 0;
	bool clear = false;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

