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
#include "../Component/MeshRender.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/Light.h"
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
	DebugMessage*		message;				// ���b�Z�[�W
	bool								mIsStart;

	unordered_map<string, GameObject*>				mGameObjectMap;			// �擾���邽�߂ɍ����GameObject�̃}�b�v
	vector<MeshRender*>											mMeshRenders;					// MeshRender��ۑ����ē���`��
	vector<Light*>														mLights;								// ���C�g�W��


	Scene();
	~Scene();

	virtual void start() {};				// �V�[���̃X�^�[�g
	virtual void update() {};			// �V�[���̍X�V
	virtual void draw() {};				// �V�[���̕`��

	// ���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	void addGameObject(string name, GameObject* gameObject);		// �V�[����GameObject�𑝉�
	GameObject* getGameObject(string name);										// �V�[������GameObject���擾
};

#endif // !_SCENE_H_

