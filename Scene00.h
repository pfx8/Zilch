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
#include "Modules\Mesh.h"
#include "Modules\Shader.h"
#include "Modules\Camera.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	DX_MESH*		m_DXMesh;		// DX用メッシュ
	Shader*		m_shader;		// シェーダー
	Camera*		m_camera;		// カメラ

	bool			m_isGameStart;	// ゲームフラグ
public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
	void SetRenderState();
};

#endif // !_SCENE00_H_

