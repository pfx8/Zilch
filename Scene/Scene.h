//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/Resources.h"
#include "../Engine/DebugMessage.h"
#include "../GameObject/GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	Resources*			mResources;		// リソース
	DebugMessage*		message;		// メッセージ
	bool				mIsStart;
	
	Scene();
	~Scene();

	virtual void start() {};			// シーンのスタート
	virtual void update() {};			// シーンの更新
	virtual void draw() {};				// シーンの描画
	virtual void setRenderState();		// レンダリング状態を設定

	// ワールド変換
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
};

#endif // !_SCENE_H_

