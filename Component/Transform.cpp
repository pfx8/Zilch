//*****************************************************************************
//
// 変換処理 [Transform.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Transform.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Transform::Transform()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Transform::~Transform()
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Transform::update()
{
	// 計算用マトリックス
	D3DXMATRIX mtxScl, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->mWorldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, mScl.x, mScl.y, mScl.z);
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&this->mRotMatrix, mRot.y, mRot.x, mRot.z);
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &this->mRotMatrix);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxTranslate);
}
