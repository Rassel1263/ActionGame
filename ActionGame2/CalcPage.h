#pragma once
class CalcPage : public ObjectUI
{
public:
	Sprite bck;
	RenderInfo ri;

	Sprite font;
	Sprite skillNum;

	std::vector<Sprite> skill;
	std::vector<std::wstring> nameGroups;


	D3DXCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	bool drawFont = false;

	int input = 0;

	float hp = 0.0f;
	float time = 0.0f;
	float combo = 0.0f;

	float stopTimer = 0.0f;
	float drawFadeTimer = 0.0f;

	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void CalcNum(float& num, float deltaTime, float speed);
};

