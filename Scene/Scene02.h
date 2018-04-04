//*****************************************************************************
//
// アニメーション処理 [Scene02.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE02_H_
#define _SCENE02_H_

#include "Scene.h"
#include "../Component/Transform.h"
#include "../Component/Camera.h"
#include "../Engine/Shader.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Engine/Plane.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene02 : public Scene
{
private:

public:
	Scene02();
	~Scene02();

	void start();			// 初期化
	void draw();			// 描画
	void oneFrame();		// 1フレームの描画内容
};
#endif // !_SCENE02_H_

