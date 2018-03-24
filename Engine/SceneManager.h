//*****************************************************************************
//
// �V�[���}�l�W���[���� [SceneManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <map>

#include "Engine.h"
#include "Scene01.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	Scene*  scene;			// �V�[��

	void ChangeRenderState();	// �����_�����O��ԍX�V
	void ChooseScene();		// �V�[����I������
public:
	SceneManager();
	~SceneManager();

	void Update();		// �V�[���̍X�V
	void Draw();			// �V�[���̕`��
}; 

#endif // !_SCENE_MANAGER_H_

