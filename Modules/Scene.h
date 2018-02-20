//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine.h"
#include "../ResourcesManager.h"
#include "../DebugMessage.h" 
#include "../Modules/Sound.h"

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*	resourcesManager;	// ���\�[�X�}�l�W�����g
	DebugMessage*		message;			// ���b�Z�[�W
	
	Scene();
	~Scene();

	virtual void Update() {};			// ���z�֐�
	virtual void Draw() {};				// ���z�֐�
	virtual void Control() {};			// �v���[���[����֐�
	virtual void SetRenderState() {};	// �����_�����O��Ԃ�ݒ�

	// ���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX* worldMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	//HRESULT LoadSceneFile(std::string name);		// ������
};

#endif // !_SCENE_H_

