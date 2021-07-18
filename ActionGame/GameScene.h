#pragma once
class GameScene : public Scene
{
public:
	Scene* next;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

