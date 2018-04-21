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
#include "CameraController.h"
#include "../Engine/Engine.h"
#include "../Engine/Shader.h"
#include "../Engine/Model/Model.h"
#include "../Scene/Scene.h"

class MeshRender : public Component
{
private:

public:
	Model*				mModel;					// 描画するモデル
	Shader*				mShader;					// 描画する用のシェーダー

	MeshRender();
	~MeshRender();

	void draw();
};

#endif // !_MESH_RENDER_H_
