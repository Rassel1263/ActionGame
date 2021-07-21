#pragma once

class SimpleShader
{
private:
	LPD3DXEFFECT shader;
public:
	SimpleShader();
	virtual ~SimpleShader();

public:
	HRESULT Prepare();
	HRESULT Begin();
	HRESULT End();

	HRESULT SetTexture(const Texture* texture);
	HRESULT SetGlowValue(float value);
	HRESULT SetColorValue(D3DXVECTOR4 outColor, D3DXVECTOR4 glowColor);

	void Render(SimpleShader* shaderManager, const Texture* texture, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 outColor, D3DXVECTOR4 glowColor, float timer);
};

