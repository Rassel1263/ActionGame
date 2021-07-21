#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR diffuse;
	D3DXVECTOR2 uv;
};

#define D3DFVF_CUSTOMVETEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Game : public Singleton<Game>
{
public:
	int screenWidth = 1280;
	int screenHeight = 720;

	float unscaleTime = 0.0f;
	float timeScale = 1.0f;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPD3DXLINE pLine;

	D3DXVECTOR2 cameraPos = { 0, 0 };
	D3DXVECTOR2 cameraScale = { 1, 1 };
	D3DXVECTOR2 cameraQuaken = { 0, 0 };
	D3DXVECTOR2 destCameraPos = cameraPos;
	D3DXVECTOR2 destCameraScale = cameraScale;
	D3DXVECTOR2 destCameraQuaken = cameraQuaken;

	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXMATRIX matWorld;

	Scene* nextScene = NULL;
public:

	~Game();
	void Init();
	void Update(float deltaTime);
	void Render();
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color);

	void ChangeScene(Scene* nextScene);
};

