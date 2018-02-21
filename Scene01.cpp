//*****************************************************************************
//
// D3DTutorial処理 [Scene01.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene01.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene01::Scene01()
{
	// Shader
	this->shader2D = new Shader;
	//this->shader3D = new Shader;

	// ライト、光方向はデフォルトで
	this->directionLight = new Light;

	//// スカイボックス
	//this->skyBox = new SkyBox;

	// フィールド
	this->field = new Plane;
	
	// 主人公
	this->woman = new Character;

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
void Scene01::Initialization()
{
	// シーン01
	std::cout << "[Information] Scene01<Zilch> " << "[" << SCREEN_WIDTH << "," << SCREEN_HEIGHT << "]" << std::endl;

	// Shader
	this->shader2D->LoadEffectFile("data/Shader/default2DRender.fx");
	//this->shader3D->LoadEffectFile("data/Shader/default3DRender.fx");

	// ライト、光方向はデフォルトで
	//this->shader->effect->SetValue("lightDir", &this->directionLight->light.Direction, sizeof(D3DXVECTOR3));
	//this->shader->effect->SetValue("lightDiffuse", &this->directionLight->light.Diffuse, sizeof(D3DXCOLOR));
	//this->shader->effect->SetValue("lightSpecular", &this->directionLight->light.Specular, sizeof(D3DXCOLOR));

	//// スカイボックス
	//this->skyBox->InitSkyBox(2500.0f);
	//this->resourcesManager->LoadTexture("skybox", &this->skyBox->titleTexture);

	// フィールド
	this->field->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(3, 3));
	this->resourcesManager->LoadTexture("field", &this->field->tex);

	// 主人公
	this->woman->InitCharacter();
	this->resourcesManager->LoadMesh("woman", this->woman->model);

	// カメラ
	this->camera->InitCameraByPlayer(this->woman);

	// 効果音
	this->seHit = LoadSound(SE_HIT);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene01::~Scene01()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(this->woman);				// プレーヤー
	RELEASE_CLASS_POINT(this->camera);				// カメラ
	RELEASE_CLASS_POINT(this->directionLight);		// ライト
	RELEASE_CLASS_POINT(this->shader2D);			// 2Dシェーダー
	//RELEASE_CLASS_POINT(this->shader3D);			// 3Dシェーダー
	RELEASE_CLASS_POINT(this->field);				// フィールド
	//RELEASE_CLASS_POINT(this->skyBox);				// トゥ―ンシェーダー

	RELEASE_CLASS_POINT(this->seHit);				// サウンド
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene01::SetRenderState()
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
void Scene01::Update()
{
	// フィールド更新
	this->field->Update();

	// カメラ更新
	this->camera->Update(this->woman);
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene01::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->field->Draw(this->shader2D, &this->camera->vMatrix, &this->camera->pMatrix);
	//this->skyBox->Draw(this->shader, &VPmatrix);
	//this->woman->model->Draw(this->shader3D, &this->camera->vMatrix, &this->camera->pMatrix);
		
	// デッバグメッセージ
	//this->woman->OutputMessage(0);
	this->camera->OutputMessage(0);
}