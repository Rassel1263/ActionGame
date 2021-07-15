#pragma once
class Spectrum : public IEffect
{
public:
	Spectrum(Sprite spr, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float visibleTime);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

