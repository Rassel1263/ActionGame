#pragma once

class PGaze : public Object
{
public:
	Player* player = NULL;


	std::vector<Sprite> gaze;

	RenderInfo pRI;
	RenderInfo hRI;

	PGaze(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

