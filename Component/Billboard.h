//*****************************************************************************
//
// �r���{�[�h���� [Billboard.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Component.h"
#include "Transform.h"
#include "Camera.h"

#include "..\Engine\Engine.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Billboard : public Component
{
private:
	Transform*			mTrans;
	D3DXMATRIX			mBillboardMatrix;

public:
	Camera*				mSceneCurrentCamera;

	Billboard(void);
	~Billboard(void);

	void start(void);
	void drawImGui(void);

	D3DXMATRIX setBillboard(void);
};

#endif // !_BILLBOARD_H_
