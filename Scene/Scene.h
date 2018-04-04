//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Component/Component.h"
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
	
	map<string, GameObject*> mGameObjects;	// �V�[���̒��ɂ��ׂĂ�gameObject��ۑ�

	Scene();
	~Scene();

	virtual void start() {};			// �V�[���̃X�^�[�g
	virtual void update() {};			// �V�[���̍X�V
	virtual void draw() {};				// �V�[���̕`��

	// ���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	// �V�[����GameObject�𑝉�
	void addGameObject(string name, GameObject* gameObject)
	{
		mGameObjects.insert({ name, gameObject });
	}

	// �V�[������GameObject���擾
	GameObject* getGameObject(string name)
	{
		if (mGameObjects.find(name) != mGameObjects.end())
		{
			return mGameObjects[name];
		}

		cout << "[Error] <GameObject> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_SCENE_H_

