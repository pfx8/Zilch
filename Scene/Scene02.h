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
#include "../Engine/Shader.h"
#include "../Engine/Model/Mesh.h"
#include "../GameObject/GameObject.h"

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

	void start();				// 初期化
};
#endif // !_SCENE02_H_

