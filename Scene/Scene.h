//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "..\Component\Camera.h"
#include "..\Component\CameraController.h"
#include "..\Component\Component.h"
#include "..\Component\MeshRender.h"
#include "..\Component\PlayerController.h"
#include "..\Component\Transform.h"
#include "..\Component\LightController.h"
#include "..\Component\Light.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"
#include "..\Engine\Shader.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	string									mName;
	D3DXVECTOR4								mBGColor;
	bool									mIsStart;
	vector<MeshRender*>						mMeshRenders;
	map<wstring, GameObject*>				mGameObjects;

	Camera*									mSystemCamera;
	Camera*									mCurrentCamera;
	Shader*									mCurrentShader;

	Scene(void);
	~Scene(void);

	virtual void start(void) {};
	void update(void);
	void draw(void);
	
	void addGameObject(wstring name, GameObject* gameObject);
	GameObject* getGameObject(wstring name);
};
#endif // !_SCENE_H_

