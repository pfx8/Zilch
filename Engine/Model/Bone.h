//*****************************************************************************
//
// 骨処理 [Bone.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BONE_H_
#define _BONE_H_

#include "..\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Bone
{
	friend class Mesh;
private:

public:
	// 骨情報
	string					mName;						// 骨の名前
	unsigned int			mIndex;						// 骨自身の番号
	D3DXMATRIX				mNodeTransform;				// 対応してノードの番号
	D3DXMATRIX				mOffset;					// モデルのルートに対して変更行列
	
	// アニメーション情報
	D3DXMATRIX				mFinaTransform;				// すべての親行列を計算した最終行列
	D3DXVECTOR3				mScl;						// 拡大縮小
	D3DXVECTOR3				mSot;						// 角度の変更

	Bone(void);
	Bone(unsigned int index, D3DXMATRIX offset, string name);
	~Bone(void);
};

#endif // !_BONE_H_

