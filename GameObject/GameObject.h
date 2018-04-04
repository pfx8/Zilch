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
#include "../Scene/Scene.h"
#include "../Component/Component.h"

class GameObject
{
	friend class Scene;

private:
	map<string, Component*> mComponents;

	void start();
	void update();

public:
	bool mActive = true;
	float mLastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

	// �C�ӃR���|�[�l���g��ǉ��ł���悤�Ƀe���v���[�g���g����
	// ������typename��Component�N���X�܂�����̌p���N���X
	template<typename T>
	void addComponent(string name, T* t)
	{
		mComponents.insert({name, t});
	}

	template<typename T>
	T* getComponent(string name)
	{
		if (mComponents.find(name) != mComponents.end())
		{
			return mComponents.find(name);
		}

		cout << "[Error] <Component> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
