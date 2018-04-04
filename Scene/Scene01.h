//*****************************************************************************
//
// ノーマルマップ処理 [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include "..\Component\Camera.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Shader.h"
#include "..\Engine\Light.h"
#include "..\Engine\Plane.h"
#include "Scene.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	string				mSceneName;
	Shader*				mShader;			// シェーダー
	//Shader*				shader3D;			// シェーダー
	Camera*				camera;				// カメラ
	Light*				light;				// ライト
	Plane*				field;				// フィールド
	//SkyBox*				skyBox;				// スカイボックス

public:
	Scene01();
	~Scene01();

	void start();	// 初期化
	void update();			// 更新
	void draw();			// 描画
	void oneFrame();		// 1フレームの描画内容
	void setRenderState();	// レンダリングを設定
};
#endif // !_SCENE00_H_

