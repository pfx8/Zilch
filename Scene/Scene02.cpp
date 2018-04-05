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
	// cube -- for test
	mResources->loadModel("cube", "Resources/Model/test.fbx");

	// skybox
	//mResources->loadTexture("skybox", "Resources/Texture/skybox.jpg");

	// 床
	//mResources->loadModel("floor", "Resources/Model/floor.fbx");
	//mResources->loadTexture("gird", "Resources/Texture/grid.png");

	// Hixo
	/*mResources->LoadTexture("HixoClothes", "Resources/Texture/HixoClothes.png");
	mResources->LoadTexture("HixoEye", "Resources/Texture/HixoEye.png");
	mResources->LoadTexture("HixoFace", "Resources/Texture/HixoFace.png");
	mResources->LoadTexture("HixoFacial", "Resources/Texture/HixoFacial.png");
	mResources->LoadTexture("HixoHair1", "Resources/Texture/HixoHair1.png");
	mResources->LoadTexture("HixoHair2", "Resources/Texture/HixoHair2.png");
	mResources->LoadTexture("HixoPanties", "Resources/Texture/HixoPanties.png");
	mResources->LoadTexture("HixoSkin", "Resources/Texture/HixoSkin.png");*/
	//mResources->loadModel("HixoModel", "Resources/Model/Hixo/FBX/Hixo2.fbx");

	// shader
	mResources->loadShader("phongShading", "Resources/Shader/phongShading.fx");

	// mainCamera
	GameObject* mainCamera = new GameObject();
	Camera* camera = new Camera();
	mainCamera->addComponent("camera", camera);
	this->addGameObject("mainCamera", mainCamera);

	// cube -- for test
	GameObject* cube = new GameObject();
	Transform* cubeTrans = new Transform();												// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	cube->addComponent("trans", cubeTrans);
	MeshRender* cubeMeshRender = new MeshRender();
	cubeMeshRender->mModel = mResources->getModel("cube");							// リソースからモデルを取得
	cubeMeshRender->mMainCamera = mainCamera;													// シーンのメインカメラを取得
	cubeMeshRender->mShader = mResources->getShader("phongShading");			// シェーダーを取得
	cube->addComponent("render", cubeMeshRender);
	cube->mIsDraw = true;
	this ->addGameObject("cube", cube);

	// player
	//GameObject* player = new GameObject();
	//Transform* playerTrans = new Transform();											// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	//player->addComponent("trans", playerTrans);
	//PlayerController* playerController = new PlayerController();
	//player->addComponent("playerCtrl", playerController);
	//this->addGameObject("player", player);

	// 床
	//GameObject* floor = new GameObject();
	//Transform* floorTrans = new Transform();												// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
	//floor->addComponent("trans", floorTrans);
	//this->addGameObject("floor", floor);

	// シェーダーにライトを設定
	/*mShader->mEffect->SetValue("lightPos", &light->pos, sizeof(D3DXVECTOR3));
	mShader->mEffect->SetValue("lightDiffuse", &light->diffuse, sizeof(D3DXVECTOR3));
	mShader->mEffect->SetFloat("lightAttenuation", light->attenuation);*/

	//// スカイボックス
	//skyBox->InitSkyBox(2500.0f);
	//resourcesManager->LoadTexture("skybox", &skyBox->titleTexture);


	// 効果音
	
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


}