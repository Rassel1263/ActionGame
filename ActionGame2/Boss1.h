#pragma once
class Boss1 : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,

		ATTACK,

		HIT,
		DIE,

		END,
	};

	Boss1();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() override;
};

