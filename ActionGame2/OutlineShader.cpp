#include "DXUT.h"
#include "OutlineShader.h"

OutlineShader::OutlineShader()
{
	shader = ShaderManager::GetInstance().GetEffect("Outline");
}

OutlineShader::~OutlineShader()
{
	shader->Release();
}

HRESULT OutlineShader::Prepare()
{
	return shader->SetTechnique(shader->GetTechniqueByName("Outline"));
}

HRESULT OutlineShader::Begin()
{
	if (FAILED(shader->Begin(NULL, 0)))
		return E_FAIL;

	return shader->BeginPass(0);
}

HRESULT OutlineShader::End()
{
	return shader->End();
}

HRESULT OutlineShader::SetTexture(const Texture* texture)
{
	if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src)))
		return E_FAIL;

	float textureSize[2] = { texture->info.Width, texture->info.Height };
	return shader->SetFloatArray(shader->GetParameterByName(0, "textureSize"), textureSize, 2);
}

HRESULT OutlineShader::SetColor(D3DXVECTOR4 color)
{
	if (FAILED(shader->SetVector(shader->GetParameterByName(0, "color"), &color)))
		return E_FAIL;
}

void OutlineShader::Render(OutlineShader* shaderManager, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 color)
{

	shaderManager->Prepare();
	shaderManager->SetTexture(sprite.GetNowScene());
	shaderManager->SetColor(color);
	shaderManager->Begin();
	sprite.Render(ri);
	shaderManager->End();
}
