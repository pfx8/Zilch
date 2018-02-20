//*****************************************************************************
//
// D3DTutorial処理 [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"

#include "Modules\Scene.h"
#include "Modules\Character.h"
#include "Modules\Camera.h"
#include "Modules\Plane.h"
#include "Modules\Light.h"
#include "Modules\Shader.h"
#include "Modules\SkyBox.h"
#include "Modules\Billboard.h"

#include "Shader\CelShader.h"
#include "Shader\ShadowMapShader.h"

#define ENEMY_MAX		(1)
#define BULLET_MAX		(21)
#define BILLBOARD_MAX	(4)

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*				camera;		// カメラ
	CelShader*			celShader;	// トゥ―ンシェーダー

	Shader*				shader;				// ベーシックシェーダー
	Plane*				sea;				// フィールド海
	Light*				directionLight;		// ライト
	SkyBox*				skyBox;				// スカイボックス

	LPDIRECTSOUNDBUFFER8 seHit;

	//BillBoard*		billboard;

	//ShadowMapShader*	shadowMap;	// シャドーマップ

public:
	Character*			ship;			// プレーヤー

	Scene00();
	~Scene00();

	void InitScene00();		// 初期化
	void Update();			// 更新
	void Draw();			// 描画
	void Control();			// 操作関数
	void SetRenderState();	// レンダリングを設定
};

#endif // !_SCENE00_H_

