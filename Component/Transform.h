//*****************************************************************************
//
// 変換処理 [Transform.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"

#include "..\Engine\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Transform : public Component
{
private:
	void update();

public:
	D3DXMATRIX		mWorldMatrix;			// ワールド変換行列
	D3DXMATRIX		mNormalMatrix;			// 法線計算用行列、回転*スケール

	D3DXVECTOR3		mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	D3DXVECTOR3		mScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// 拡大縮小
	D3DXVECTOR3		mRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 角度

	Transform();
	virtual ~Transform();

	void drawImGui();						// ImGuiでTransformのデータを出す
};

#endif // !_TRANSFORM_H_
