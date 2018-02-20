//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "FbxSDK.h"
#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\DebugMessage.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*		m_resourcesManager;	// ���\�[�X�}�l�W�����g
	DebugMessage*		m_message;		// ���b�Z�[�W
	FBX_SDK*				m_fbxSdk;		// FbxSDK
	
	Scene();
	~Scene();

	virtual void Update() {};		// ���z�֐�
	virtual void Draw() {};		// ���z�֐�
	virtual void Control() {};	// �v���[���[����֐�
	virtual void SetRenderState() {};		// �����_�����O��Ԃ�ݒ�
	virtual bool FromFbxSceneToScene();	// fbxSDk�ɂ���ēǂݍ��񂾃f�[�^��������Scene�N���X�ɓ����
};

#endif // !_SCENE_H_

