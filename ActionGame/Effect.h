#pragma once
class Effect : public IEffect
{
public:
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float visibleTime = 0.0f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

