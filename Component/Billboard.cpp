//*****************************************************************************
//
// ビルボード処理 [Billboard.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Billboard.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Billboard::Billboard()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Billboard::~Billboard()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Billboard::start()
{
	// ビルボードの変換行列を取得
	this->mTrans = this->mGameObject->getComponent<Transform>();
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Billboard::update()
{
	// カメラからビルボードまでの方向ベクトルを計算
	D3DXVECTOR3 cameraPos = this->mMainCamera->getComponent<Transform>()->mPos;
	D3DXVECTOR3 cameraDir = cameraPos - this->mTrans->mPos;
	
	// Y軸には関係ないのでｍここでY軸の数値を捨てて、正規化して方向ベクトルができる
	cameraDir = D3DXVECTOR3(cameraDir.x, 0.0f, cameraDir.z);
	D3DXVec3Normalize(&cameraDir, &cameraDir);

	// カメラのビューイング行列を取得
	D3DXMATRIX viewMatrix = mMainCamera->getComponent<Camera>()->mViewMatrix;
	// ビルボード行列を作る
	D3DXMATRIX billboardMatrix;
	D3DXMatrixIdentity(&billboardMatrix);
	billboardMatrix._11 = viewMatrix._11;
	billboardMatrix._13 = viewMatrix._13;
	billboardMatrix._31 = viewMatrix._31;
	billboardMatrix._33 = viewMatrix._33;

	// 逆行列を計算
	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	// ビルボードのワールド変換行列を更新
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	this->mTrans->mWorldMatrix = billboardMatrix * temp;
}