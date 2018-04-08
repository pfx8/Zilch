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
	mIsStart = true;

	//-----------------------
	// リソースを読み込み
	//-----------------------

	// 床
	resource->loadTexture("grid", "Resources/Texture/grid.png");
	resource->loadModel("gridField", "Resources/Model/gridField.fbx");

	// Hixo
	resource->loadTexture("clothes", "Resources/Texture/Hixo/HixoClothes.png");
	resource->loadTexture("eye", "Resources/Texture/Hixo/HixoEye.png");
	resource->loadTexture("face", "Resources/Texture/Hixo/HixoFace.png");
	resource->loadTexture("facial", "Resources/Texture/Hixo/HixoFacial.png");
	resource->loadTexture("hair1", "Resources/Texture/Hixo/HixoHair1.png");
	resource->loadTexture("hair2", "Resources/Texture/Hixo/HixoHair2.png");
	resource->loadTexture("panties", "Resources/Texture/Hixo/HixoPanties.png");
	resource->loadTexture("skin", "Resources/Texture/Hixo/HixoSkin.png");
	resource->loadModel("HixoModel", "Resources/Model/Hixo2k.fbx");

	// shader
	resource->loadShader("phongShading", "Resources/Shader/phongShading.fx");

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();																// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridField->addComponent<Transform>("trans", gridFieldTrans);
	CameraController* cameraController = new CameraController();
	cameraController->mMainCamera = mainCamera;
	gridField->addComponent<CameraController>("cameraController", cameraController);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = resource->getModel("gridField");						// リソースからモデルを取得
	gridFieldMeshRender->mMainCamera = mainCamera;												// シーンのメインカメラを取得
	gridFieldMeshRender->mShader = resource->getShader("phongShading");			// シェーダーを取得
	gridField->addComponent<MeshRender>("meshRender", gridFieldMeshRender);
	this ->addGameObject("gridField", gridField);

	// mainCamera
	camera->mCameraPos = D3DXVECTOR3(0.0f, 5.0f, 10.0f);
	camera->mTargetTrans = gridFieldTrans;
	mainCamera->addComponent<Camera>("camera", camera);
	this->addGameObject("mainCamera", mainCamera);

	// player
	//GameObject* player = new GameObject();
	//Transform* playerTrans = new Transform();											// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	//player->addComponent("trans", playerTrans);
	//PlayerController* playerController = new PlayerController();
	//player->addComponent("playerCtrl", playerController);
	//this->addGameObject("player", player);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{

}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene02::draw()
{
	for (auto it : mMeshRenders)
	{
		it->draw();
	}
}