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

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GameObject
{
	friend class Scene;
	friend class GUI;

private:
	// typeid(classPoint)�𗘗p���Ċecomponent��type_index���擾�A�����ă}�b�v�ɕۑ�
	map<type_index, Component*>		mComponents;

	void start(void);
	void update(void);

public:
	Scene*			mParentScene;
	bool			mIsDraw = false;
	bool			mIsActive = true;
	float			mLastActiveTime = 0;			// �O��X�V��������

	GameObject(void);
	virtual ~GameObject(void);

	//*****************************************************************************
	//
	// �C��Component��GameObject�ɓ����
	//
	// ������<typename T>��Component�N���X�̌p���N���X
	//
	//*****************************************************************************
	template<typename T> void addComponent(T* component)
	{
		// �Y�t�������R���|�[�l���g�̒��ɏ���GameObject�̃|�C���^������
		component->mParentGameObject = this;

		// MeshRender�������GameObject��`��
		if (typeid(T) == typeid(MeshRender))
		{
			this->mIsDraw = true;
		}

		mComponents.insert({ typeid(T), component });
	}

	//*****************************************************************************
	//
	// �N���X�^�C�v�ɂ����Component��߂�
	//
	// ������<typename T>��Component�̌p���N���X
	//
	// <����> dynamic_cast<type*>(e)
	// type�͕K���N���X�^�Ae�͕K���|�C���^(nullptr�̓_��)
	// e�͕K��type�N���X�^��type�̌p���N���X�^
	// �����ăx�[�X�N���X�̒��Ƀ|�����[�t�B�b�N�Ȍ^���K�v
	// <�߂�l> e�̃N���X�^�̃|�C���^
	//
	//*****************************************************************************
	template<typename T> T* getComponent()
	{
		if (this->mComponents.find(typeid(T)) != this->mComponents.end())
		{
			return dynamic_cast<T*>(this->mComponents[typeid(T)]);
		}

		cout << "[Error] <Component> Get " << typeid(T).name() << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
