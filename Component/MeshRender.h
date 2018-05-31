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
	Shader*				mShader;					// 描画する用のシェーダー(byシーン)

	char				mModelPathTemp[MAX_PATH];	// モデルパス
	char				mTexPathTemp[MAX_PATH];		// テクスチャパス

	void start();									// 初期化
	void update();									// 更新

public:
	bool				mIsOutline = false;			// アウトラインチェック
	float				mOutLineFactor;				// アウトラインベクトルを計算する時、頂点ベクトルと法線ベクトルんを混ざる因子数
	float				mOutLineStrength;			// アウトライン太さ

	bool				mIsDrawShadow = false;		// シャドウチェック
	Model*				mModel;						// 描画するモデル
	Shader*				mShadowMapShader;			// シャドウマップシェーダー
	ShadowMap*			mShadowMap;					// シャドウマップ

	MeshRender();
	~MeshRender();

	void draw();									// メッシュを描画
	void drawShadowMap();							// シャドウマップを描画
	void drawImGui();								// ImGuiでMeshRenderのデータを出す
};

#endif // !_MESH_RENDER_H_
