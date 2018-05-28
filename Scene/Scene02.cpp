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
	cout << "<Scene> " << "[Project:Zilch] " << SCREEN_WIDTH << " * " << SCREEN_HEIGHT << endl;
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
	resource->createModel(L"Resources\\Model\\field.fbx");

	// Hixo
	//resource->createModel(L"Resources\\Model\\Hixo.fbx");
	//resource->getModel(L"Hixo")->addAnimation(new Animation(L"Resources/Model/Running.fbx"));

	// nanosuit
	resource->createModel(L"Resources\\Model\\nanosuit\\nanosuit.obj");

	// light
	resource->createModel(L"Resources\\Model\\light.fbx");

	// Flag -- bone testing
	//resource->createModel(L"Resources\\Model\\flag.fbx");

	// shader
	resource->createShader(L"Resources\\Shader\\mainShader.fx");
	resource->createShader(L"Resources\\Shader\\shadowMap.fx");

	// シーンのデフォルトシェーダーを指定
	this->mShader = resource->getShader(L"mainShader");

	// ライト
	GameObject* light = new GameObject();
	Transform* lightTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	lightTrans->mPos = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	light->addComponent<Transform>(lightTrans);
	Light* singleLight = new Light();
	// ライトタイプを指定
	singleLight->mLightType = LT_point;
	singleLight->mLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	// ライト範囲は50ｍにする
	// data by http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	singleLight->mPointLight.constant = 1.0f;
	singleLight->mPointLight.linear = 0.9f;
	singleLight->mPointLight.quadratic = 0.032f;
	singleLight->mLightPos = lightTrans->mPos;
	light->addComponent<Light>(singleLight);
	MeshRender* lightMeshRender = new MeshRender();
	lightMeshRender->mModel = resource->getModel(L"light");					// リソースからモデルを取得
	this->mMeshRenders.push_back(lightMeshRender);							// MeshRenderをシーンに追加
	light->addComponent<MeshRender>(lightMeshRender);
	this->addGameObject(L"light", light);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	player->addComponent<Transform>(playerTrans);
	CameraController* cameraController = new CameraController();			// カメラコントローラ
	player->addComponent<CameraController>(cameraController);
	LightController* lightController = new LightController();				// ライトコントローラ
	lightController->mLight = singleLight;										// ライトを指定
	player->addComponent<LightController>(lightController);
	MeshRender* playerMeshRender = new MeshRender();
	playerMeshRender->mModel = resource->getModel(L"nanosuit");				// リソースからモデルを取得
	playerMeshRender->mIsDrawShadow = true;									// シャドウマップ描画
	playerMeshRender->mShadowMapShader = resource->getShader(L"shadowMap");	// シャドウマップシェーダーを取得
	this->mMeshRenders.push_back(playerMeshRender);							// MeshRenderをシーンに追加
	player->addComponent<MeshRender>(playerMeshRender);
	this->addGameObject(L"player", player);

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
	gridFieldMeshRender->mModel = resource->getModel(L"field");			// リソースからモデルを取得
	this->mMeshRenders.push_back(gridFieldMeshRender);					// MeshRenderをシーンに追加
	gridField->addComponent<MeshRender>(gridFieldMeshRender);
	this->addGameObject(L"床", gridField);

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