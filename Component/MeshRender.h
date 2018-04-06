//*****************************************************************************
//
// メッシュ描画処理 [MeshRender.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _MESH_RENDER_H_
#define _MESH_RENDER_H_

#include "Component.h"
#include "Camera.h"
#include "../Engine/Engine.h"
#include "../Engine/Shader.h"
#include "../Engine/Model/Model.h"

class MeshRender : public Component
{
private:
	void start();

public:
	GameObject*		mMainCamera;				// 描画するため使ってるカメラが必要
	Model*				mModel;							// 描画するモデル
	Shader*				mShader;						// 描画する用のシェーダー

	MeshRender();
	~MeshRender();

	void draw();
};

#endif // !_MESH_RENDER_H_
