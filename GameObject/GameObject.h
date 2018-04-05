//*****************************************************************************
//
// GameObject [GameObject.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "../Engine/Engine.h"
#include "../Component/Component.h"

class GameObject
{
	friend class Scene;

private:
	vector<Component*>									mComponents;				// �R���|�[�l���g�R���e�i
	unordered_map<string, Component*>		mComponentsMap;		// ���O���̃R���|�[�l���g�}�b�v

	void start();
	void update();

public:
	bool mActive = true;
	bool mIsDraw = false;
	float mLastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

	template<typename T> void addComponent(string name, T* t);			// �C�ӃR���|�[�l���g��ǉ��ł���悤�Ƀe���v���[�g���g����
	template<typename T> T* getComponent(string name);						// ���O�ɂ���ăR���|�[�l���g�擾
};

#endif // !_GAME_OBJECT_H_
