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
template<typename T>
class Node
{
private:

public:
	string				mName;			// ノードの名前
	vector<Node<T>*>	mChildren;		// 子供ノードポインタ集合
	Node<T>*			mParent;		// 親ノードポインタ
	T*					mData;			// ノードデータ

	Node(string name);
	~Node(void);

};

#endif // !_NODE_H_

