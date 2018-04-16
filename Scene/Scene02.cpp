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
	resource->loadModel("gridField", "Resources/Model/field.fbx");

	// Hixo
	resource->loadTexture("clothes", "Resources/Texture/Hixo/clothes.png");
	resource->loadTexture("eye", "Resources/Texture/Hixo/eye.png");
	resource->loadTexture("face", "Resources/Texture/Hixo/face.png");
	resource->loadTexture("facial", "Resources/Texture/Hixo/facial.png");
	resource->loadTexture("hair1", "Resources/Texture/Hixo/hair1.png");
	resource->loadTexture("hair2", "Resources/Texture/Hixo/hair2.png");
	resource->loadTexture("panties", "Resources/Texture/Hixo/panties.png");
	resource->loadTexture("skin", "Resources/Texture/Hixo/skin.png");
	//resource->loadModel("Hixo", "Resources/Model/Shachiku_chan_Ver2.0.fbx");
	resource->loadModel("Hixo", "Resources/Model/Hixo.fbx");

	// shader
	resource->loadShader("phongShading", "Resources/Shader/phongShading.fx");

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();
	camera->cameraPos = D3DXVECTOR3(0.0f, 4.0f, -5.0f);

	// player
	GameObject* player = new GameObject();
	Transform* playerTrans = new Transform();											// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	playerTrans->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->addComponent<Transform>("trans", playerTrans);
	PlayerController* playerController = new PlayerController();
	player->addComponent<PlayerController>("playerController", playerController);
	CameraController* cameraController = new CameraController();
	cameraController->mainCamera = mainCamera;
	player->addComponent<CameraController>("cameraController", cameraController);
	MeshRender* playerMeshRender = new MeshRender();
	playerMeshRender->model = resource->getModel("Hixo");							// リソースからモデルを取得
	playerMeshRender->shader = resource->getShader("phongShading");			// シェーダーを取得
	player->addComponent<MeshRender>("meshRender", playerMeshRender);
	this->addGameObject("player", player);

	// mainCamera
	camera->targetTrans = playerTrans;
	mainCamera->addComponent<Camera>("camera", camera);
	this->addGameObject("mainCamera", mainCamera);

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();																// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridField->addComponent<Transform>("trans", gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->model = resource->getModel("gridField");						// リソースからモデルを取得
	gridFieldMeshRender->shader = resource->getShader("phongShading");			// シェーダーを取得
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