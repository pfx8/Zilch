﻿//*****************************************************************************
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
	// シーン01
	cout << "<Scene02>" << "<" << SCREEN_WIDTH << "," << SCREEN_HEIGHT << "> : [Project : Zilch] " << endl;
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
	resource->createTexture("Resources/Texture/grid.png");
	resource->createModel("Resources/Model/field.fbx", MT_default);

	// Hixo
	resource->createTexture("Resources/Texture/Hixo2/clothes.png");
	resource->createTexture("Resources/Texture/Hixo2/eye.png");
	resource->createTexture("Resources/Texture/Hixo2/face.png");
	resource->createTexture("Resources/Texture/Hixo2/facial.png");
	resource->createTexture("Resources/Texture/Hixo2/hair1.png");
	resource->createTexture("Resources/Texture/Hixo2/hair2.png");
	resource->createTexture("Resources/Texture/Hixo2/panties.png");
	resource->createTexture("Resources/Texture/Hixo2/skin.png");
	resource->createModel("Resources/Model/Hixo.fbx", MT_withBone);
	resource->getModel("Hixo")->addAnimation(new Animation("Resources/Model/Running.fbx"));

	// Flag -- bone testing
	resource->createTexture("Resources/Texture/flag/heart.png");
	resource->createTexture("Resources/Texture/flag/wood.jpg");
	resource->createModel("Resources/Model/flag.fbx", MT_withBone);

	// shader
	resource->createShader("Resources/Shader/phongShading.fx");
	resource->createShader("Resources/Shader/celShading.fx");
	resource->createShader("Resources/Shader/shadowMap.fx");

	// シーンのデフォルトシェーダーを指定
	this->mShader = resource->getShader("celShading");

	// ライト
	GameObject* pointLight = new GameObject();
	Light* light = new Light;
	// ライトタイプを指定
	light->mLightType = LT_point;
	//light->mLightDirection = D3DXVECTOR3(1.0f, 1.0f, -0.5f);
	light->mLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	light->mLightPos = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	// ライト範囲は50ｍにする
	// data by http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	light->mPointLight.constant = 1.0f;
	light->mPointLight.linear = 0.9f;
	light->mPointLight.quadratic = 0.032f;
	pointLight->addComponent<Light>(light);
	this->addGameObject("light", pointLight);

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();
	camera->mCameraPos = D3DXVECTOR3(0.0f, 4.0f, 5.0f);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();									// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	player->addComponent<Transform>(playerTrans);
	CameraController* cameraController = new CameraController();
	cameraController->mMainCamera = mainCamera;
	player->addComponent<CameraController>(cameraController);
	//MeshRender* playerMeshRender = new MeshRender();
	//playerMeshRender->mModel = resource->getModel("Hixo");					// リソースからモデルを取得
	//playerMeshRender->mIsDrawShadow = true;									// シャドウマップ描画
	//playerMeshRender->mShadowMapShader = resource->getShader("shadowMap");	// シャドウマップシェーダーを取得
	//this->mMeshRenders.push_back(playerMeshRender);							// MeshRenderをシーンに追加
	//player->addComponent<MeshRender>(playerMeshRender);
	this->addGameObject("player", player);

	// mainCamera
	camera->mTargetTrans = playerTrans;
	mainCamera->addComponent<Camera>(camera);
	this->addGameObject("mainCamera", mainCamera);

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();							// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridFieldTrans->mScl = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
	gridField->addComponent<Transform>(gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = resource->getModel("field");				// リソースからモデルを取得
	this->mMeshRenders.push_back(gridFieldMeshRender);						// MeshRenderをシーンに追加
	gridField->addComponent<MeshRender>(gridFieldMeshRender);
	this->addGameObject("gridField", gridField);

	// Flag -- bone testing
	GameObject* flag = new GameObject();
	Transform* flagTrans = new Transform();									// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	flag->addComponent<Transform>(flagTrans);
	MeshRender* flagMeshRender = new MeshRender();
	flagMeshRender->mModel = resource->getModel("flag");					// リソースからモデルを取得
	this->mMeshRenders.push_back(flagMeshRender);							// MeshRenderをシーンに追加
	flag->addComponent<MeshRender>(flagMeshRender);
	this->addGameObject("flag", flag);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{

}