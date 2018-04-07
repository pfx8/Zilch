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
	bool			mActive = true;						// �g���Ă�}�[�N
	float		mLastActiveTime = 0;			// �O��X�V��������

	GameObject();
	virtual ~GameObject();

	// �C�ӃR���|�[�l���g��ǉ��ł���悤�Ƀe���v���[�g���g����
	// ������typename��Component�N���X�܂�����̌p���N���X
	template<typename T> void addComponent(string name, T* t)
	{
		mComponents.push_back(t);
		mComponentsMap.insert({ name, t });
	}

	// ���O�ɂ���ăR���|�[�l���g�擾
	// ������typename��Component�N���X�܂�����̌p���N���X
	template<typename T> T* getComponent(string name)
	{
		if (mComponentsMap.find(name) != mComponentsMap.end())
		{
			//------------------------------------------------------------
			// dynamic_cast<type*>(e)
			// type�͕K���N���X�^�Ae�͕K���|�C���^(nullptr�̓_��)
			//
			// �d�v : e�͕K��type�N���X�^��type�̌p���N���X�^
			//
			// �߂�l : e�̃N���X�^�̃|�C���^
			//------------------------------------------------------------
			return dynamic_cast<T*>(mComponentsMap[name]);
		}

		cout << "[Error] <Component> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
