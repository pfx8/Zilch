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
#include "../Engine/Engine.h"

class Transform : public Component
{
private:
	void update();

public:
	D3DXMATRIX			worldMatrix;			// ワールド変換行列

	D3DXVECTOR3		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	D3DXVECTOR3		scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// 拡大縮小
	D3DXVECTOR3		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 角度

	Transform();
	virtual ~Transform();

};

#endif // !_TRANSFORM_H_
