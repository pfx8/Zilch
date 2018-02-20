//*****************************************************************************
//
// D3DTutorial処理 [Scene00.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene00.h"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene00::Scene00()
{
	// スタートフラグ
	m_isGameStart = true;

	// メッシュ初期化
	m_DXMesh = new DX_MESH;
	m_fbxSdk->LoadFbxScene(m_resourcesManager->GetFbxPath("testP"));
	m_fbxSdk->FbxMeshToDirectXMesh(m_DXMesh);
	m_DXMesh->MakeBuffer();

	// シェーダー初期化
	m_shader = new Shader;
	m_shader->InitShader();

	// カメラ初期化
	m_camera = new Camera;
	m_camera->InitCamera();

	// Test
	/*while (m_DXMesh->m_vertex != NULL)
	{
		std::cout << m_DXMesh->m_vertex->position.x
			<< m_DXMesh->m_vertex->position.y
			<< m_DXMesh->m_vertex->position.z
			<< std::endl;

		(m_DXMesh->m_vertex)++;
	}*/
	//for (int count = 0; count < m_DXMesh->m_vertexIndexNum; )
	//{
	//	std::cout << "(" << m_DXMesh->m_vertexIndex[count] << ","
	//		<< m_DXMesh->m_vertexIndex[count + 1] << ","
	//		<< m_DXMesh->m_vertexIndex[count + 2] << ")"
	//		<< std::endl;

	//	count += 3;
	//}
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene00::~Scene00()
{
	RELEASE_CLASS_POINT(m_DXMesh);
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	Control();	// 各操作の更新
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene00::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(53, 53, 53, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		m_DXMesh->DrawDXMesh();

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}


//*****************************************************************************
//
// 操作関数
//
//*****************************************************************************
void Scene00::Control()
{
	if (m_isGameStart == true)
	{
		m_DXMesh->DrawDXMesh();
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN))	// key Enter
		{
			m_isGameStart = true;
		}
	}
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene00::SetRenderState()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// レンダーステートパラメータの設定
	//GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	//GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	//GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	//GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	//// サンプラーステートパラメータの設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	//// テクスチャステージステートの設定
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// Set the default render states
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// Set the default texture stage states
	//pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// Set the default texture filters
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}
