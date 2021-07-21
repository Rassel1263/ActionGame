#pragma once

struct Texture
{
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	std::map<std::wstring, Texture*> textures;

public:
	virtual ~TextureManager();

	const Texture* GetTexture(std::wstring filePath);
	void Reset();
};

