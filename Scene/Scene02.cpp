//*****************************************************************************
//
// アニメーション処理 [Scene02.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene02.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene02::Scene02()
{
	// Shader
	this->mShader = new Shader;
	//this->shader3D = new Shader;

	// ライト、光方向はデフォルトで
	this->light = new Light;

	//// スカイボックス
	//this->skyBox = new SkyBox;

	// フィールド
	this->field = new Plane;
	
	// 主人公
	this->mHixo = new Character;

	// カメラ
	this->camera = new Camera;

	// 初期化
	Initialization();
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Scene02::Initialization()
{
	// シーン01
	cout << "[Information] Scene02 <アニメーション> " << "[" << SCREEN_WIDTH << "," << SCREEN_HEIGHT << "]" << endl;

	// Shader
	this->mShader->LoadEffectFile("Resources/Shader/render3D_phong.fx");
	//this->shader3D->LoadEffectFile("Resources/Shader/default3DRender.fx");

	// シェーダーにライトを設定
	this->mShader->effect->SetValue("lightPos", &this->light->pos, sizeof(D3DXVECTOR3));
	this->mShader->effect->SetValue("lightDiffuse", &this->light->diffuse, sizeof(D3DXVECTOR3));
	this->mShader->effect->SetFloat("lightAttenuation", this->light->attenuation);

	//// スカイボックス
	//this->skyBox->InitSkyBox(2500.0f);
	//this->resourcesManager->LoadTexture("skybox", &this->skyBox->titleTexture);

	// フィールド
	this->field->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(1, 1));
	this->resourcesManager->LoadTexture("grid", &this->field->tex);

	// カメラ
	this->camera->InitCameraByPlayer(this->mHixo);

	// player
	//this->mHixo->model->

	// 効果音
	
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(this->mHixo);				// プレーヤー
	RELEASE_CLASS_POINT(this->camera);				// カメラ
	RELEASE_CLASS_POINT(this->light);				// ライト
	RELEASE_CLASS_POINT(this->mShader);				// シェーダー
	RELEASE_CLASS_POINT(this->field);				// フィールド
	//RELEASE_CLASS_POINT(this->skyBox);			// トゥ―ンシェーダー

}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene02::SetRenderState()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// レンダーステートパラメータの設定
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene02::Update()
{
	// フィールド更新
	this->field->Update();

	// カメラ更新
	this->camera->Update(this->mHixo);
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene02::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		oneFrame(); // 描画

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// 1フレームの描画内容
//
//*****************************************************************************
void Scene02::oneFrame()
{
	this->field->Draw(this->mShader, this->camera);
	//this->skyBox->Draw(this->shader, &VPmatrix);

	// デッバグメッセージ
	//this->camera->OutputMessage(0);
}