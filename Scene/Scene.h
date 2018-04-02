//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "..\Engine\Engine.h"
#include "..\Engine\ResourcesManager.h"
#include "..\Engine\DebugMessage.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*	mResourcesManager;	// ���\�[�X�}�l�W�����g
	DebugMessage*		message;			// ���b�Z�[�W
	
	Scene();
	~Scene();

	virtual void Update() {};			// �V�[���̍X�V
	virtual void Draw() {};				// �V�[���̕`��
	virtual void oneFrame() {};			// 1�t���[���̕`����e
	virtual void Control() {};			// �v���[���[����֐�
	virtual void SetRenderState() {};	// �����_�����O��Ԃ�ݒ�

	// ���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
};

#endif // !_SCENE_H_

