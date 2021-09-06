#pragma once

class Scene
{
public:
	Player* player = NULL;

	ObjectManager obm;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();
};

