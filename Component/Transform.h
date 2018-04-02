//*****************************************************************************
//
// 変換処理 [Transform.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "..\Engine\Engine.h"
#include "Component.h"

class Transform : public Component
{
private:
	void start();
	void update();

public:
	D3DXMATRIX  mTransformMat;

	D3DXVECTOR3 mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 mScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 mRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Transform();
	virtual ~Transform();

};

#endif // !_TRANSFORM_H_
