#pragma once
class ResultScreen : public Object
{
public:
	bool bFade = true;

	float score = 0;
	float hp = 0;
	float time = 0;

	std::vector<Sprite> ui;

	Sprite fade;
	RenderInfo ri;

	ResultScreen();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void CalcNum(float& num);
};

