#pragma once
class Spectrum : public Object
{
public:
	Sprite spr;
	RenderInfo ri;
	D3DXVECTOR4 color = { 0, 0, 0, 0 };

	ColorShader* colorShader = NULL;

	Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

};

