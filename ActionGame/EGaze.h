#pragma once
class EGaze : public Object
{ 
public:
	Sprite spr[2];
	RenderInfo ri;
	Enemy* enemy;

	EGaze(Enemy* enemy);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

