//*****************************************************************************
//
// Assimp�m�[�h���� [Node.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _NODE_H_
#define _NODE_H_

#include "..\Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
template<typename T>
class Node
{
private:

public:
	string				mName;			// �m�[�h�̖��O
	vector<Node<T>*>	mChildren;		// �q���m�[�h�|�C���^�W��
	Node<T>*			mParent;		// �e�m�[�h�|�C���^
	T*					mData;			// �m�[�h�f�[�^

	Node(string name);
	~Node();

};

#endif // !_NODE_H_

