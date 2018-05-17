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
#include "Camera.h"

#include "..\Engine\Engine.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Billboard : public Component
{
private:
	Transform*			mTrans;						// ビルボード情報

	void start();
	void update();

public:
	GameObject*			mSceneCurrentCamera;		// マインカメラ

	Billboard();
	~Billboard();
};

#endif // !_BILLBOARD_H_
