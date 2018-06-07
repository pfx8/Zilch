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
Scene02::Scene02(void)
{
	// シーンの情報
	cout << "<Scene> " << "[Project:Zilch] " << SCREEN_WIDTH << " * " << SCREEN_HEIGHT << endl;
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Scene02::start(void)
{
	Resources* resource = getResources();

	//-----------------------
	// リソースを読み込み
	//-----------------------

	// 床
	resource->createModel(L"Resources\\Model\\field.fbx");

	// Hixo
	resource->createModel(L"Resources\\Model\\Hixo.fbx");
	//resource->getModel(L"Hixo")->addAnimation(new Animation(L"Resources/Model/Running.fbx"));

	// light model
	resource->createModel(L"Resources\\Model\\light.fbx");

	// billboard
	resource->createModel(L"Resources\\Model\\billboard.fbx");

	// shader
	resource->createShader(L"Resources\\Shader\\mainShader.fx");
	resource->createShader(L"Resources\\Shader\\shadowMap.fx");

	// シーンのデフォルトシェーダーを指定
	this->mCurrentShader = resource->getShader(L"mainShader");

	// ライト
	GameObject* light = new GameObject();
	Transform* lightTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	lightTrans->mPos = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	lightTrans->mScl = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	light->addComponent<Transform>(lightTrans);
	Light* singleLight = new Light();
	singleLight->mLightType = LT_point;										// ライトタイプを指定
	singleLight->mLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	singleLight->mPointLight.constant = 1.0f;
	singleLight->mPointLight.linear = 0.9f;
	singleLight->mPointLight.quadratic = 0.032f;
	singleLight->mLightPos = lightTrans->mPos;
	light->addComponent<Light>(singleLight);
	MeshRender* lightMeshRender = new MeshRender();
	lightMeshRender->mModel = resource->getModel(L"light");
	this->mMeshRenders.push_back(lightMeshRender);							// MeshRenderをシーンに追加
	light->addComponent<MeshRender>(lightMeshRender);
	this->addGameObject(L"Light", light);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	player->addComponent<Transform>(playerTrans);
	CameraController* cameraController = new CameraController();
	player->addComponent<CameraController>(cameraController);
	PlayerController* playerController = new PlayerController();
	player->addComponent<PlayerController>(playerController);
	LightController* lightController = new LightController();
	lightController->mCurrentLight = singleLight;									// コントローラライトを指定
	player->addComponent<LightController>(lightController);
	MeshRender* playerMeshRender = new MeshRender();
	playerMeshRender->mModel = resource->getModel(L"Hixo");
	playerMeshRender->mIsDrawShadow = true;									// シャドウマップを設定
	playerMeshRender->mShadowMapShader = resource->getShader(L"shadowMap");
	this->mMeshRenders.push_back(playerMeshRender);							// MeshRenderをシーンに追加
	player->addComponent<MeshRender>(playerMeshRender);
	this->addGameObject(L"Player", player);

	// システムカメラ設定
	this->mSystemCamera = new Camera();
	this->mSystemCamera->start();
	this->mSystemCamera->mCameraPos = D3DXVECTOR3(0.0f, 4.0f, 5.0f);
	this->mSystemCamera->mTargetPos = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	this->mSystemCamera->mIsVerticalLimited = false;
	this->mSystemCamera->mIsZoomLimited = false;

	// シーンカメラを設定(デフォルトはシステムカメラ);
	this->mCurrentCamera = this->mSystemCamera;

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();						// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridFieldTrans->mScl = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
	gridField->addComponent<Transform>(gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = resource->getModel(L"field");
	this->mMeshRenders.push_back(gridFieldMeshRender);					// MeshRenderをシーンに追加
	gridField->addComponent<MeshRender>(gridFieldMeshRender);
	this->addGameObject(L"床", gridField);

	// ビルボード
	//GameObject* billboard = new GameObject();
	//Transform* billTrans = new Transform();
	//billTrans->mRot.x = 90.0;											// X軸に90度を回転
	//billTrans->mPos.y = 3;
	//billboard->addComponent<Transform>(billTrans);
	//MeshRender* billboardMeshRender = new MeshRender();
	//billboardMeshRender->mModel = resource->getModel(L"billboard");
	//this->mMeshRenders.push_back(billboardMeshRender);					// MeshRenderをシーンに追加
	//billboard->addComponent<MeshRender>(billboardMeshRender);
	//Billboard* billB = new Billboard();
	//billB->mSceneCurrentCamera = this->mCurrentCamera;
	//billboard->addComponent<Billboard>(billB);
	//this->addGameObject(L"ビルボード", billboard);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02(void)
{
	RELEASE_CLASS_POINT(this->mSystemCamera);
	RELEASE_CLASS_POINT(this->mCurrentCamera);
	RELEASE_CLASS_POINT(this->mCurrentShader);
}