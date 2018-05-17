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
class Node
{
private:

public:
	string				mName;			// �m�[�h�̖��O
	vector<Node*>		mChildren;		// �q���m�[�h�|�C���^�W��
	Node*				mParent;		// �e�m�[�h�|�C���^
	D3DXMATRIX			mTransform;		// �m�[�h�̕ϊ��s��

	Node(string name);
	~Node();

};

#endif // !_NODE_H_

