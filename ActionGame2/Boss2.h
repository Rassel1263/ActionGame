#pragma once
class Boss2 : public CBoss
{
public:
	Boss2();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() override;

	virtual bool Pattern1(float deltaTime) override;
	virtual bool Pattern2(float deltaTime) override;
	virtual bool Pattern3(float deltaTime) override;

	virtual int ChoosePattern();
};

