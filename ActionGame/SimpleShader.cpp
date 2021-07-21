#include "DXUT.h"

SimpleShader::SimpleShader()
{
	shader = ShaderManager::GetInstance().GetEffect("Simple");
}

SimpleShader::~SimpleShader()
{
	shader = NULL;
}

HRESULT SimpleShader::Prepare()
{
	return shader->SetTechnique(shader->GetTechniqueByName("Simple"));
}

HRESULT SimpleShader::Begin()
{
	if (FAILED(shader->Begin(NULL, 0)))
		return E_FAIL;

	return shader->BeginPass(0);
}

HRESULT SimpleShader::End()
{
	return shader->End();
}

HRESULT SimpleShader::SetTexture(const Texture* texture)
{
	if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "SpriteTexture"), texture->src)))
		return E_FAIL;

	float textureSize[2] = { texture->info.Width, texture->info.Height };
	return shader->SetFloatArray(shader->GetParameterByName(0, "xTextureSize"), textureSize, 2);
}

HRESULT SimpleShader::SetGlowValue(float value)
{
	return shader->SetFloat(shader->GetParameterByName(0, "xGlowValue"), value);
}

HRESULT SimpleShader::SetColorValue(D3DXVECTOR4 outColor, D3DXVECTOR4 glowColor)
{
	HRESULT hr;

	hr = shader->SetFloatArray(shader->GetParameterByName(0, "xOutlineColor"), D3DXVECTOR4(outColor.x, outColor.y, outColor.z, 1.0f), 4);
	hr = shader->SetFloatArray(shader->GetParameterByName(0, "xOutGlowColor"), D3DXVECTOR4(glowColor.x, glowColor.y, glowColor.z, 0.8f), 4);

	return hr;
}

void SimpleShader::Render(SimpleShader* shaderManager, const Texture* texture, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 outColor, D3DXVECTOR4 glowColor, float timer)
{
	shaderManager->Prepare();
	shaderManager->SetGlowValue(timer);
	shaderManager->SetTexture(texture);
	shaderManager->SetColorValue(outColor, glowColor);
	shaderManager->Begin();
	sprite.Render(ri);
	shaderManager->End();
}

