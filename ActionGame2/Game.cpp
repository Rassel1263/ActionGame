#include "DXUT.h"

Scene* nowScene = NULL;

void Game::Check()
{
#ifdef _DEBUG
	screenHeight = 1040;
#endif // _DEBUG
}

Game::~Game()
{
	if (pVB != NULL)
		pVB->Release();

	for (auto& thread : threads)
	{
		if (thread.joinable())
			thread.join();
	}

	SAFE_RELEASE(pLine);
}

HRESULT Game::Init()
{
	if (FAILED(DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0)))
	{
		return E_FAIL;
	}

	D3DXCreateLine(DXUTGetD3D9Device(), &pLine);
	// Turn off culling
	DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn off D3D lighting
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Turn on the zbuffer
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZENABLE, TRUE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	ChangeScene(new MainScene());

	Camera::GetInstance().Init();
	Input::GetInstance().Start();

	/*TextureManager::GetInstance().SaveFilePath();
	spr.Init();

	for (int i = 0; i < 12; i++)
		threads.emplace_back(&TextureManager::LoadTexture, &TextureManager::GetInstance(), i);*/
}

void Game::Update(float deltaTime)
{
	//if (TextureManager::GetInstance().textureLoad)
	{
		Input::GetInstance().Update();

		if (nextScene)
		{
			SAFE_DELETE(nowScene);

			nowScene = nextScene;
			nowScene->Init();
			nextScene = NULL;
		}

		if (Input::GetInstance().KeyDown(VK_CONTROL))
			timeScale = 0.05f;
		if (Input::GetInstance().KeyUp(VK_CONTROL))
			timeScale = 1.0f;

		unscaleTime = deltaTime;

		if (nowScene)
			nowScene->Update(deltaTime * timeScale);

		Camera::GetInstance().Update(deltaTime);
	}
	//else spr.Update(deltaTime);
}

void Game::Render()
{
	//if(TextureManager::GetInstance().textureLoad)
	{
		if(nowScene)
			nowScene->Render();

		D3DXMATRIX matProj;
		D3DXMatrixOrthoLH(&matProj, Game::GetInstance().screenWidth, Game::GetInstance().screenHeight, 0.01f, 1000.0f);
		DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);

		if(nowScene)
			nowScene->UIRender();
	}
	//else spr.Render();
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;
}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color)
{
	pLine->SetWidth(2.0f);
	pLine->Begin();
	D3DXVECTOR3 v[] = { D3DXVECTOR3(p1.x, p1.y, 0.0f), D3DXVECTOR3(p2.x, p2.y, 0.0f) };
	D3DXMATRIX retMat = matrix * Camera::GetInstance().matWorld * Camera::GetInstance().matView * Camera::GetInstance().matProj;
	pLine->DrawTransform(v, 2, &retMat, color);
	pLine->End();
}

void Game::Reset()
{
	DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0);

}
