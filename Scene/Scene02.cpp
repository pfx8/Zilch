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
	cout << "[Information] Scene02 <アニメーション> " << "[" << SCREEN_WIDTH << "," << SCREEN_HEIGHT << "]" << endl;
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Scene02::start()
{
	mIsStart = true;

	// リソースを読み込み
	{
		// test
		//mResources->loadModel("test", "Resources/Model/test.fbx");

		// skybox
		mResources->loadTexture("skybox", "Resources/Texture/skybox.jpg");

		// 床
		mResources->loadTexture("gird", "Resources/Texture/grid.png");

		// Hixo
		/*mResources->LoadTexture("HixoClothes", "Resources/Texture/HixoClothes.png");
		mResources->LoadTexture("HixoEye", "Resources/Texture/HixoEye.png");
		mResources->LoadTexture("HixoFace", "Resources/Texture/HixoFace.png");
		mResources->LoadTexture("HixoFacial", "Resources/Texture/HixoFacial.png");
		mResources->LoadTexture("HixoHair1", "Resources/Texture/HixoHair1.png");
		mResources->LoadTexture("HixoHair2", "Resources/Texture/HixoHair2.png");
		mResources->LoadTexture("HixoPanties", "Resources/Texture/HixoPanties.png");
		mResources->LoadTexture("HixoSkin", "Resources/Texture/HixoSkin.png");*/
		mResources->loadModel("HixoModel", "Resources/Model/Hixo/FBX/Hixo_noEnd.fbx");

		// shader
		mResources->loadShader("phongShading", "Resources/Shader/phongShading.fx");
	}

	// player
	GameObject* player = new GameObject();

	// シェーダーにライトを設定
	/*mShader->mEffect->SetValue("lightPos", &light->pos, sizeof(D3DXVECTOR3));
	mShader->mEffect->SetValue("lightDiffuse", &light->diffuse, sizeof(D3DXVECTOR3));
	mShader->mEffect->SetFloat("lightAttenuation", light->attenuation);*/

	//// スカイボックス
	//skyBox->InitSkyBox(2500.0f);
	//resourcesManager->LoadTexture("skybox", &skyBox->titleTexture);

	// フィールド
	field->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(1, 1));

	// カメラ
	//camera->InitCameraByPlayer(mHixo);

	// player
	//mHixo->model->

	// 効果音
	
}

//*****************************************************************************
//
// 資源を読み込み
//
//*****************************************************************************
void Scene02::loading()
{
	
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(mHixo);				// プレーヤー
	//RELEASE_CLASS_POINT(camera);				// カメラ
	RELEASE_CLASS_POINT(light);				// ライト
	RELEASE_CLASS_POINT(mShader);				// シェーダー
	RELEASE_CLASS_POINT(field);				// フィールド
	//RELEASE_CLASS_POINT(skyBox);			// トゥ―ンシェーダー

}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene02::setRenderState()
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
void Scene02::update()
{
	// フィールド更新
	field->update();

	// カメラ更新
	//camera->Update(mHixo);
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene02::draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		oneFrame(); // 描画

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// 1フレームの描画内容
//
//*****************************************************************************
void Scene02::oneFrame()
{
	//field->Draw(mShader, camera);
	//skyBox->Draw(shader, &VPmatrix);

	// デッバグメッセージ
	//camera->OutputMessage(0);
}