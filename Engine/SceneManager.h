//*****************************************************************************
//
// �V�[���}�l�W���[���� [SceneManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Engine.h"
#include "input.h"

#include "..\Scene\Scene.h"
#include "..\Scene\Scene02.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	unordered_map<string, Scene*>	mScenes;				// �V�[���}�b�v

public:
	Scene*							mCurrentScene;			// ���̃V�[���|�C���^

	SceneManager();
	~SceneManager();

	void start();				// �ŏ��̃V�[����������
	void update();				// �V�[�����X�V
	void draw();				// �V�[����`��

	void addScene(string name, Scene* scene);		// �V�[���𑝉�
	HRESULT setActiveScene(string name);			// ���ꂩ����s����V�[����I��
}; 

#endif // !_SCENE_MANAGER_H_

