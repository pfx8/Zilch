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
#include "../Engine/Engine.h"
#include "../Engine/Shader.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Engine/Plane.h"
#include "../Engine/Model/Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene02 : public Scene
{
private:
	string				mSceneName;
	Shader*				mShader;			// シェーダー
	//Camera*				camera;				// カメラ
	Light*				light;				// ライト
	Plane*				field;				// フィールド
	//SkyBox*				skyBox;				// スカイボックス

public:
	Character*			mHixo;			// プレーヤー

	Scene02();
	~Scene02();

	void start();			// 初期化
	void loading();			// 資源を読み込み
	void Update();			// 更新
	void Draw();			// 描画
	void oneFrame();		// 1フレームの描画内容
	void SetRenderState();	// レンダリングを設定
};
#endif // !_SCENE02_H_

