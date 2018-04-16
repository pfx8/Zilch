//*****************************************************************************
//
// 骨処理 [Bone.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BONE_H_
#define _BONE_H_

#include "../Engine.h"

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
	unsigned int					mIndex;								// 
	D3DXMATRIX					mNodeTransform;				// 
	D3DXMATRIX					mOffset;								// 
	
	// アニメーション情報
	D3DXMATRIX					mLastTransform;				// 最後計算できた行列
	D3DXVECTOR3				mScl;									// 拡大縮小
	D3DXVECTOR3				mSot;									// 角度の変更

	Bone();
	Bone(unsigned int index, D3DXMATRIX offset);
	~Bone();
};

#endif // !_BONE_H_

