//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Component/Camera.h"
#include "../Component/CameraController.h"
#include "../Component/Component.h"
#include "../Component/MeshRender.h"
#include "../Component/PlayerController.h"
#include "../Component/Transform.h"
#include "../Component/Light.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"
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
	DebugMessage*				mMessage;		// ���b�Z�[�W
	bool						mIsStart;		// �X�^�[�g�}�[�N

	vector<MeshRender*>								mMeshRenders;			// ���b�V�������_�����O
	unordered_map<string, GameObject*>				mGameObjectMap;			// �擾���邽�߂ɍ����GameObject�̃}�b�v

	Scene();
	~Scene();

	virtual void start() {};			// �V�[���̃X�^�[�g

	void update();						// �V�[���̍X�V
	void draw();						// �V�[���̕`��
	
	void addGameObject(string name, GameObject* gameObject);		// �V�[����GameObject�𑝉�
	GameObject* getGameObject(string name);							// �V�[������GameObject���擾
};
#endif // !_SCENE_H_

