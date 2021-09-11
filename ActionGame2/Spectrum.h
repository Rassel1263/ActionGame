#pragma once
class Spectrum : public Object
{
public:
	Sprite spr;
	RenderInfo ri;
	D3DXVECTOR4 color = { 0, 0, 0, 0 };

	ColorShader* colorShader = NULL;

	float attackTime = 0.0f;
	float maxAttackTime = 0.0f;

	int attackNum = 0;

	Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color, int layer);
	Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color, int layer, float curAttackTime, float maxAttackTime, int attackNum);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

};

