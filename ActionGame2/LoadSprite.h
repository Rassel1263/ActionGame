#pragma once
class LoadSprite : public Object
{
public:
	Sprite intro;

	Sprite progress;
	Sprite progressBck;

	int size = 0.0f;
	int maxSize = 0.0f;


	void Init();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

