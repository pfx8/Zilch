//*****************************************************************************
//
// Assimpノード処理 [Node.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _NODE_H_
#define _NODE_H_

#include "..\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Node
{
private:

public:
	string				mName;			// ノードの名前
	vector<Node*>		mChildren;		// 子供ノードポインタ集合
	Node*				mParent;		// 親ノードポインタ
	D3DXMATRIX			mTransform;		// ノードの変換行列

	Node(string name);
	~Node();

};

#endif // !_NODE_H_

