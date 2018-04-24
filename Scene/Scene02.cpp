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
	// シーン01
	cout << "[Information] Scene02 <Project : Zilch> " << "[" << SCREEN_WIDTH << "," << SCREEN_HEIGHT << "]" << endl;
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
	resource->loadTexture("grid", "Resources/Texture/grid.png");
	resource->loadModel(MT_default,"gridField", "Resources/Model/field.fbx");

	// Hixo
	resource->loadTexture("clothes", "Resources/Texture/Hixo2/clothes.png");
	resource->loadTexture("eye", "Resources/Texture/Hixo2/eye.png");
	resource->loadTexture("face", "Resources/Texture/Hixo2/face.png");
	resource->loadTexture("facial", "Resources/Texture/Hixo2/facial.png");
	resource->loadTexture("hair1", "Resources/Texture/Hixo2/hair1.png");
	resource->loadTexture("hair2", "Resources/Texture/Hixo2/hair2.png");
	resource->loadTexture("panties", "Resources/Texture/Hixo2/panties.png");
	resource->loadTexture("skin", "Resources/Texture/Hixo2/skin.png");
	resource->loadModel(MT_withBone, "Hixo", "Resources/Model/Hixo.fbx");
	resource->getModel("Hixo")->addAnimation(new Animation("Resources/Model/Running.fbx"));

	// shader
	resource->loadShader("phongShading", "Resources/Shader/phongShading.fx");
	resource->loadShader("celShading", "Resources/Shader/celShading.fx");
	resource->loadShader("shadowMap", "Resources/Shader/ShadowMap.fx");
	
	// ライト
	GameObject* pointLight = new GameObject();
	Light* light = new Light;
	//light->mLightDirection = D3DXVECTOR3(1.0f, 1.0f, -0.5f);
	light->mLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	light->mLightPos = D3DXVECTOR3(2.0f, 4.0f, 1.0f);
	// ライト範囲は7ｍにする
	// data by http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	light->mPointLight.constant = 1.0f;
	light->mPointLight.linear = 0.9f;
	light->mPointLight.quadratic = 0.032f;
	pointLight->addComponent<Light>("light", light);
	this->addGameObject("pointLight", pointLight);

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();
	camera->mCameraPos = D3DXVECTOR3(0.0f, 4.0f, 5.0f);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();								// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	playerTrans->mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->addComponent<Transform>("trans", playerTrans);
	PlayerController* playerController = new PlayerController();
	player->addComponent<PlayerController>("playerController", playerController);
	CameraController* cameraController = new CameraController();
	cameraController->mMainCamera = mainCamera;
	player->addComponent<CameraController>("cameraController", cameraController);
	MeshRender* playerMeshRender = new MeshRender();
	playerMeshRender->mModel = resource->getModel("Hixo");					// リソースからモデルを取得
	playerMeshRender->mShader = resource->getShader("celShading");			// シェーダーを取得
	playerMeshRender->mIsDrawShadow = true;									// シャドウマップ描画
	playerMeshRender->mShadowMapShader = resource->getShader("shadowMap");	// シャドウマップシェーダーを取得
	this->mMeshRenders.push_back(playerMeshRender);							// MeshRenderをシーンに追加
	player->addComponent<MeshRender>("meshRender", playerMeshRender);
	this->addGameObject("player", player);

	// mainCamera
	camera->mTargetTrans = playerTrans;
	mainCamera->addComponent<Camera>("camera", camera);
	this->addGameObject("mainCamera", mainCamera);

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();							// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridFieldTrans->mScl = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
	gridField->addComponent<Transform>("trans", gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = resource->getModel("gridField");			// リソースからモデルを取得
	gridFieldMeshRender->mShader = resource->getShader("phongShading");		// シェーダーを取得
	this->mMeshRenders.push_back(gridFieldMeshRender);						// MeshRenderをシーンに追加
	gridField->addComponent<MeshRender>("meshRender", gridFieldMeshRender);
	this->addGameObject("gridField", gridField);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{

}