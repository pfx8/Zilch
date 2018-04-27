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
#include "../Engine/ShadowMap.h"
#include "../Engine/Model/Model.h"
#include "../Scene/Scene.h"

class MeshRender : public Component
{
private:
	Shader*				mShader;				// 描画する用のシェーダー(byシーン)

	void start();								// 初期化
	void update();								// 更新

public:
	bool				mIsDrawShadow;			// シャドウチェック
	Model*				mModel;					// 描画するモデル
	Shader*				mShadowMapShader;		// シャドウマップシェーダー
	ShadowMap*			mShadowMap;				// シャドウマップ

	MeshRender();
	~MeshRender();

	void draw();								// メッシュを描画
	void drawShadowMap();						// シャドウマップを描画
};

#endif // !_MESH_RENDER_H_
