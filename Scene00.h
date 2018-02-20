//*****************************************************************************
//
// D3DTutorial���� [Scene00.h]
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
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	DX_MESH*		m_DXMesh;		// DX�p���b�V��
	Shader*		m_shader;		// �V�F�[�_�[
	Camera*		m_camera;		// �J����

	bool			m_isGameStart;	// �Q�[���t���O
public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
	void SetRenderState();
};

#endif // !_SCENE00_H_

