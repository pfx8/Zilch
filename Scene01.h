//*****************************************************************************
//
// D3DTutorial処理 [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"
#include "Character.h"
#include "Modules\Scene.h"
#include "Modules\Camera.h"
#include "Modules\Light.h"
#include "Modules\SkyBox.h"
#include "Modules\Shader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	Shader*				shader2D;			// シェーダー
	//Shader*				shader3D;			// シェーダー
	Camera*				camera;				// カメラ
	Light*				directionLight;		// ライト
	Plane*				field;				// フィールド
	//SkyBox*				skyBox;				// スカイボックス

	LPDIRECTSOUNDBUFFER8 seHit;

public:
	Character*			woman;			// プレーヤー

	Scene01();
	~Scene01();

	void Initialization();	// 初期化
	void Update();			// 更新
	void Draw();			// 描画
	void SetRenderState();	// レンダリングを設定
};
#endif // !_SCENE00_H_

