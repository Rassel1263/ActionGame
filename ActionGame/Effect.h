#pragma once
class Effect : public IEffect
{
public:
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale = { 1, 1 }, float aniMaxTime = 0.1f, float visibleTime = 0.0f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

