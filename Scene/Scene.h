//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "..\Engine\Engine.h"
#include "..\Engine\ResourcesManager.h"
#include "..\Engine\DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*	mResourcesManager;	// リソースマネジメント
	DebugMessage*		message;			// メッセージ
	
	Scene();
	~Scene();

	virtual void Update() {};			// シーンの更新
	virtual void Draw() {};				// シーンの描画
	virtual void oneFrame() {};			// 1フレームの描画内容
	virtual void Control() {};			// プレーヤー操作関数
	virtual void SetRenderState() {};	// レンダリング状態を設定

	// ワールド変換
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
};

#endif // !_SCENE_H_

