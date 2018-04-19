//*****************************************************************************
//
// 変換処理 [Transform.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "MeshRender.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
MeshRender::MeshRender()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
MeshRender::~MeshRender()
{

}

//*****************************************************************************
//
// ドロー
//
//*****************************************************************************
void MeshRender::draw()
{
	// モデルのワールド変換行列を取得
	Transform* trans = this->mGameObject->getComponent<Transform>("trans");
	// モデルのワールド変換行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);

	// カメラ情報を取得
	Camera* camera = this->mGameObject->mScene->getGameObject("mainCamera")->getComponent<Camera>("camera");
	// カメラの行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	mModel->draw(this->mShader, trans, camera);
}
