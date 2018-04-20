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
#include "../Engine/Engine.h"

class Billboard : public Component
{
private:
	Transform*			mTrans;				// �r���{�[�h���

	void start();
	void update();

public:
	GameObject*			mMainCamera;			// �}�C���J����

	Billboard();
	~Billboard();
};

#endif // !_BILLBOARD_H_
