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
	// シーンの情報
	cout << "<Scene>: " << "[Project:Zilch] " << SCREEN_WIDTH << " * " << SCREEN_HEIGHT << endl;
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Scene02::start()
{
	Resources* resource = getResources();

	//-----------------------
	// リソースを読み込み
	//-----------------------

	// 床
	//resource->createTexture("Resources/Texture/grid.png");
	resource->createModel("Resources/Model/field.fbx");

	// Hixo
	//resource->createTexture("Resources/Texture/Hixo/clothes.png");
	//resource->createTexture("Resources/Texture/Hixo/eye.png");
	//resource->createTexture("Resources/Texture/Hixo/face.png");
	//resource->createTexture("Resources/Texture/Hixo/facial.png");
	//resource->createTexture("Resources/Texture/Hixo/hair1.png");
	//resource->createTexture("Resources/Texture/Hixo/hair2.png");
	//resource->createTexture("Resources/Texture/Hixo/panties.png");
	//resource->createTexture("Resources/Texture/Hixo/skin.png");
	resource->createModel("Resources/Model/Hixo.fbx");
	resource->getModel("Hixo")->addAnimation(new Animation("Resources/Model/Running.fbx"));

	// Flag -- bone testing
	//resource->createTexture("Resources/Texture/flag/heart.png");
	//resource->createTexture("Resources/Texture/flag/wood.jpg");
	//resource->createModel("Resources/Model/flag.fbx", MT_withBone);

	// shader
	resource->createShader("Resources/Shader/mainShader.fx");
	resource->createShader("Resources/Shader/shadowMap.fx");

	// シーンのデフォルトシェーダーを指定
	this->mShader = resource->getShader("mainShader");

	// ライト
	GameObject* pointLight = new GameObject();
	Light* light = new Light();
	// ライトタイプを指定
	light->mLightType = LT_point;
	light->mLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	light->mLightPos = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	// ライト範囲は50ｍにする
	// data by http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	light->mPointLight.constant = 1.0f;
	light->mPointLight.linear = 0.9f;
	light->mPointLight.quadratic = 0.032f;
	pointLight->addComponent<Light>(light);
	this->addGameObject("light", pointLight);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	player->addComponent<Transform>(playerTrans);
	CameraController* cameraController = new CameraController();
	player->addComponent<CameraController>(cameraController);
	MeshRender* playerMeshRender = new MeshRender();
	playerMeshRender->mModel = resource->getModel("Hixo");					// リソースからモデルを取得
	playerMeshRender->mIsDrawShadow = true;									// シャドウマップ描画
	playerMeshRender->mShadowMapShader = resource->getShader("shadowMap");	// シャドウマップシェーダーを取得
	this->mMeshRenders.push_back(playerMeshRender);							// MeshRenderをシーンに追加
	player->addComponent<MeshRender>(playerMeshRender);
	this->addGameObject("player", player);

	// システムカメラ設定
	this->mSystemCamera = new Camera();
	this->mSystemCamera->start();
	this->mSystemCamera->mCameraPos = D3DXVECTOR3(0.0f, 4.0f, 5.0f);
	this->mSystemCamera->mTargetTrans = playerTrans;
	this->mSystemCamera->mIsVerticalLimited = false;
	this->mSystemCamera->mIsZoomLimited = false;

	// シーンカメラを設定(デフォルトはシステムカメラ);
	this->mCurrentCamera = this->mSystemCamera;

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();							// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridFieldTrans->mScl = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
	gridField->addComponent<Transform>(gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = resource->getModel("field");			// リソースからモデルを取得
	this->mMeshRenders.push_back(gridFieldMeshRender);					// MeshRenderをシーンに追加
	gridField->addComponent<MeshRender>(gridFieldMeshRender);
	this->addGameObject("gridField", gridField);

	// Flag -- bone testing
	//GameObject* flag {new GameObject()};
	//Transform* flagTrans {new Transform()};								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	//flag->addComponent<Transform>(flagTrans);
	//MeshRender* flagMeshRender {new MeshRender()};
	//flagMeshRender->mModel = resource->getModel("flag");					// リソースからモデルを取得
	//this->mMeshRenders.push_back(flagMeshRender);							// MeshRenderをシーンに追加
	//flag->addComponent<MeshRender>(flagMeshRender);
	//this->addGameObject("flag", flag);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{
	RELEASE_CLASS_POINT(this->mSystemCamera);
	RELEASE_CLASS_POINT(this->mCurrentCamera);
	RELEASE_CLASS_POINT(this->mShader);
}