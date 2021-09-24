#pragma once

struct Texture
{
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager : public Singleton<TextureManager>
{
	std::mutex lock;
	std::mutex insertLock;

	std::map<std::wstring, Texture*> textures;
public:
	int fileSize = 0;
	int threadCount = 0;

	//bool textureLoad = false;

	std::queue<std::wstring> filePaths;

	~TextureManager();
	void SaveFilePath();
	void LoadTexture(int n);
	const Texture* GetTexture(std::wstring filePath);
	void ResetDevice();
	void Term();
};

