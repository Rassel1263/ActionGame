#pragma once

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos; // The position
	D3DCOLOR color;    // The color
	D3DXVECTOR2 uv;
};


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Game : public Singleton<Game>
{
public:
	std::vector<std::thread> threads;

	bool pause = false;

	float screenWidth = 1920;
	float screenHeight = 1080;

	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

	LPDIRECT3DVERTEXBUFFER9 pVB = NULL; // Buffer to hold vertices

	LPD3DXLINE pLine;

	Scene* nextScene = NULL;

	void Check();

	virtual ~Game();
	HRESULT Init();
	void Update(float deltaTime);
	void Render();
	void ChangeScene(Scene* nextScene);
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color);

	void Reset();
	void Term();

};

