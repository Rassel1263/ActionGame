#include "DXUT.h"
#include "Sprite.h"
namespace fs = std::filesystem;

void Sprite::LoadAll(std::wstring filePath, float aniTime, bool aniLoop)
{
	textures.clear();

	if (fs::is_directory(filePath))
	{
		for (auto file : fs::recursive_directory_iterator(filePath))
		{
			if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
				textures.push_back(texture);
		}
	}
	else
	{
		if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
			textures.push_back(texture);
		else
			textures.push_back(TextureManager::GetInstance().GetTexture(L"ActionGame.jpg"));
	}

	szScene = textures.size() - 1;
	this->aniMaxTime = aniTime;
	this->bAniLoop = aniLoop;
}

void Sprite::Update(float deltaTime)
{
	if (bAnimation)
	{
		if (!bAniStop)
			aniTimer += deltaTime;

		if (aniTimer > aniMaxTime)
		{
			aniTimer = 0;

			if (scene < szScene)
				scene++;
			else if (bAniLoop)
				scene = 0;
			else
				bAnimation = false;
		}
	}
}

void Sprite::Render(const RenderInfo& ri)
{
	VOID* data;
	Game::GetInstance().pVB->Lock(0, 0, &data, 0);

	CUSTOMVERTEX v[4];
	v[0].pos = D3DXVECTOR3(0.0f, (float)GetNowScene()->info.Height, 0.0f);
	v[0].diffuse = color;
	v[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	v[1].pos = D3DXVECTOR3((float)GetNowScene()->info.Width * widthRatio, (float)GetNowScene()->info.Height, 0.0f);
	v[1].diffuse = color;
	v[1].uv = D3DXVECTOR2(1.0f * widthRatio, 0.0f);
	v[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v[2].diffuse = color;
	v[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	v[3].pos = D3DXVECTOR3((float)GetNowScene()->info.Width * widthRatio, 0.0f, 0.0f);
	v[3].diffuse = color;
	v[3].uv = D3DXVECTOR2(1.0f * widthRatio, 1.0f);
	memcpy(data, (void*)v, sizeof(v));
	Game::GetInstance().pVB->Unlock();

	D3DXMATRIX matrix;
	D3DXVECTOR2 centerPos = { GetNowScene()->info.Width * ri.pivot.x, GetNowScene()->info.Height * ri.pivot.y };
	D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, -D3DXToRadian(ri.rotate), &(ri.pos - centerPos));

	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, (bCamera) ? &(matrix * Game::GetInstance().matWorld) : &matrix);
	DXUTGetD3D9Device()->SetStreamSource(0, Game::GetInstance().pVB, 0, sizeof(CUSTOMVERTEX));
	DXUTGetD3D9Device()->SetFVF(D3DFVF_CUSTOMVETEX);
	DXUTGetD3D9Device()->SetTexture(0, GetNowScene()->src);
	DXUTGetD3D9Device()->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
}

const Texture* Sprite::GetNowScene()
{
	return textures[scene];
}

void Sprite::Reset()
{
	bAnimation = true;
	aniTimer = 0;
	scene = 0;
}
