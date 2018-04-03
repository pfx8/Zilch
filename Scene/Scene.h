//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/Resources.h"
#include "../Engine/DebugMessage.h"
#include "../GameObject/GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:

public:
	Resources*			mResources;		// ���\�[�X
	DebugMessage*		message;		// ���b�Z�[�W
	bool				mIsStart;
	
	Scene();
	~Scene();

	virtual void start() {};			// �V�[���̃X�^�[�g
	virtual void update() {};			// �V�[���̍X�V
	virtual void draw() {};				// �V�[���̕`��
	virtual void setRenderState();		// �����_�����O��Ԃ�ݒ�

	// ���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
};

#endif // !_SCENE_H_

