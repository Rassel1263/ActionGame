#include "DXUT.h"
#include "Game.h"

Scene* nowScene = NULL;

Game::~Game()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pLine);
}

void Game::Init()
{
	ChangeScene(new GameScene());

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -10.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixOrthoLH(&matProj, screenWidth / 2, screenHeight / 2, 0.01f, 1000.0f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);

	DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0,
		D3DFVF_CUSTOMVETEX, D3DPOOL_DEFAULT, &pVB, 0);

	D3DXCreateLine(DXUTGetD3D9Device(), &pLine);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Alpha texture blend setting
	DXUTGetD3D9Device()->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHABLENDENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	Input::GetInstance().Start();

	srand(time(NULL));
}

void Game::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if (nextScene)
	{
		nowScene = nextScene;
		nowScene->Init();
		nextScene = NULL;
	}

	D3DXVec2Lerp(&cameraPos, &cameraPos, &destCameraPos, 0.1f);
	D3DXVec2Lerp(&cameraScale, &cameraScale, &destCameraScale, 0.1f);
	D3DXVec2Lerp(&cameraQuaken, &cameraQuaken, &destCameraQuaken, 0.1f);

	D3DXMATRIXA16 matCamScale;
	D3DXMatrixScaling(&matCamScale, cameraScale.x, cameraScale.y, 1.0f);
	D3DXMATRIXA16 matCamPos;
	D3DXMatrixTranslation(&matCamPos, ((rand() % 2 ? 1 : -1) * cameraQuaken.x) - cameraPos.x, ((rand() % 2 ? 1 : -1) * cameraQuaken.y) - cameraPos.y, 0.0f);
	matWorld = matCamScale * matCamPos;
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &matWorld);

	if (nowScene)
		nowScene->Update(deltaTime);
}

void Game::Render()
{

	if (nowScene)
		nowScene->Render();
}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color)
{
	pLine->SetWidth(2.0f);
	pLine->Begin();
	D3DXVECTOR3 v[] = { D3DXVECTOR3(p1.x, p1.y, 0.0f), D3DXVECTOR3(p2.x, p2.y, 0.0f) };
	D3DXMATRIX retMat = matrix * matWorld * matView * matProj;
	pLine->DrawTransform(v, 2, &retMat, color);
	pLine->End();
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;
}
