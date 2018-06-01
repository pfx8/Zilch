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
	Transform*			mTrans;						// ビルボード位置情報

public:
	GameObject*			mSceneCurrentCamera;

	Billboard(void);
	~Billboard(void);

	void start(void);
	void update(void);
};

#endif // !_BILLBOARD_H_
