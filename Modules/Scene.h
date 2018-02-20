//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine.h"
#include "../ResourcesManager.h"
#include "../DebugMessage.h" 
#include "../Modules/Sound.h"

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*	resourcesManager;	// リソースマネジメント
	DebugMessage*		message;			// メッセージ
	
	Scene();
	~Scene();

	virtual void Update() {};			// 仮想関数
	virtual void Draw() {};				// 仮想関数
	virtual void Control() {};			// プレーヤー操作関数
	virtual void SetRenderState() {};	// レンダリング状態を設定

	// ワールド変換
	void SetWorldMatrix(D3DXMATRIX* worldMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ファイル(blender)からシンーの資源を読み込み
	//HRESULT LoadSceneFile(std::string name);		// 未完成
};

#endif // !_SCENE_H_

