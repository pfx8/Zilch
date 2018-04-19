//*****************************************************************************
//
// ビルボード処理 [Billboard.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Component.h"
#include "Transform.h"
#include "../Engine/Engine.h"

class Billboard : public Component
{
private:
	Transform			mTrans;				// ビルボード情報
	Transform*			mCameraTrans;		// カメラ情報

	void start() {};
	void update() {};

public:
	GameObject*			mGameObject;					// 所属GameObjectの他のコンポーネントを取れるように
	bool					mStart = false;				// スタートマック

	Billboard();
	virtual ~Billboard();
};

#endif // !_BILLBOARD_H_
