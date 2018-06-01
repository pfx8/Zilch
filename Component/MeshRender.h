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
#include "Light.h"

#include "..\Engine\Engine.h"
#include "..\Engine\Shader.h"
#include "..\Engine\ShadowMap.h"
#include "..\Engine\Model\Model.h"

#include "..\GameObject\GameObject.h"

#include "..\Scene\Scene.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class MeshRender : public Component
{
private:
	Shader*				mCurrentShader;

	char				mModelPathTemp[MAX_PATH];	// モデルパス
	char				mTexPathTemp[MAX_PATH];		// テクスチャパス

public:
	bool				mIsDrawOutline = false;
	float				mOutLineFactor;				// アウトラインベクトルを計算する時、頂点ベクトルと法線ベクトルんを混ざる因子数
	float				mOutLineStrength;			// アウトライン太さ

	Model*				mModel;

	bool				mIsDrawShadow = false;
	Shader*				mShadowMapShader;
	ShadowMap*			mShadowMap;

	MeshRender(void);
	~MeshRender(void);

	void start(void);
	void update(void);
	void drawImGui(void);
	void drawGameObject(void);
	void drawShadowMap(void);
};

#endif // !_MESH_RENDER_H_
