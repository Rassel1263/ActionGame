#pragma once
class Main : public Object
{
public:
	static bool intro;

	Sprite introSpr;
	std::vector<Sprite> ui;

	int cNum = 0;
	int pNum = -1;

	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoiceBtn();
};

