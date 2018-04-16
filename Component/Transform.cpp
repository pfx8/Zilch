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
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);
}
