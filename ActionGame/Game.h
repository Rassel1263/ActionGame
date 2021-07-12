#pragma once

struct LineData
{
	D3DXVECTOR2 p1;
	D3DXVECTOR2 p2;
	D3DXMATRIX mat;
	D3DXCOLOR color;
};

class Game : public Singleton<Game>
{
public:
	float screenWidth = 1920;
	float screenHeight = 1080;

	float timeScale = 1.0f;

	float TaskHeight = 0;

	float fixedDeltaTime = 0.0f, fixedTime = 1.0f / 60.0f;
	float unscaleTime = 0.0f;

	D3DXMATRIX matProj;
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;

	LPD3DXSPRITE pSprite;
	LPD3DXLINE pLine;

	D3DXVECTOR2 cameraPos = { 0.0f, 0.0f };
	D3DXVECTOR2 destCameraPos = cameraPos;
	D3DXVECTOR2 cameraScale = { 1.0f, 1.0f };
	D3DXVECTOR2 destCameraScale = cameraScale;
	D3DXVECTOR2 cameraQuaken = { 0.0f, 0.0f };
	D3DXVECTOR2 destCameraQuaken = cameraQuaken;

	std::queue<LineData> lines;
	Scene* nextScene = NULL;

	virtual ~Game();
	void Init();
	void Update(float deltaTime);
	void Render();
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX mat, D3DXCOLOR color);
	void ChangeScene(Scene* nextScene);
	
	D3DXVECTOR2 ScreenSize();
};

