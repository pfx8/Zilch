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
	mIsStart = true;

	//-----------------------
	// リソースを読み込み
	//-----------------------

	// 床
	//mResources->loadTexture("gird", "Resources/Texture/grid.png");
	mResources->loadModel("gridField", "Resources/Model/gridField.fbx");


	// Hixo
	/*mResources->LoadTexture("HixoClothes", "Resources/Texture/HixoClothes.png");
	mResources->LoadTexture("HixoEye", "Resources/Texture/HixoEye.png");
	mResources->LoadTexture("HixoFace", "Resources/Texture/HixoFace.png");
	mResources->LoadTexture("HixoFacial", "Resources/Texture/HixoFacial.png");
	mResources->LoadTexture("HixoHair1", "Resources/Texture/HixoHair1.png");
	mResources->LoadTexture("HixoHair2", "Resources/Texture/HixoHair2.png");
	mResources->LoadTexture("HixoPanties", "Resources/Texture/HixoPanties.png");
	mResources->LoadTexture("HixoSkin", "Resources/Texture/HixoSkin.png");*/
	mResources->loadModel("HixoModel", "Resources/Model/Hixo/FBX/Hixo2.fbx");

	// shader
	mResources->loadShader("phongShading", "Resources/Shader/phongShading.fx");

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();
	mainCamera->addComponent("camera", camera);
	this->addGameObject("mainCamera", mainCamera);

	// 床
	GameObject* gridField = new GameObject();
	Transform* gridFieldTrans = new Transform();																	// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	gridField->addComponent("trans", gridFieldTrans);
	MeshRender* gridFieldMeshRender = new MeshRender();
	gridFieldMeshRender->mModel = mResources->getModel("gridField");						// リソースからモデルを取得
	gridFieldMeshRender->mMainCamera = mainCamera;													// シーンのメインカメラを取得
	gridFieldMeshRender->mShader = mResources->getShader("phongShading");			// シェーダーを取得
	gridField->addComponent("meshRender", gridFieldMeshRender);
	this ->addGameObject("gridField", gridField);

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