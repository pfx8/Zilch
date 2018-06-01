//*****************************************************************************
//
// ���b�V���`�揈�� [MeshRender.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _MESH_RENDER_H_
#define _MESH_RENDER_H_

#include "Component.h"
#include "Camera.h"
#include "CameraController.h"
#include "Light.h"

#include "..\Engine\Engine.h"
#include "..\Engine\Shader.h"
#include "..\Engine\ShadowMap.h"
#include "..\Engine\Model\Model.h"

#include "..\GameObject\GameObject.h"

#include "..\Scene\Scene.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class MeshRender : public Component
{
private:
	Shader*				mCurrentShader;

	char				mModelPathTemp[MAX_PATH];	// ���f���p�X
	char				mTexPathTemp[MAX_PATH];		// �e�N�X�`���p�X

public:
	bool				mIsDrawOutline = false;
	float				mOutLineFactor;				// �A�E�g���C���x�N�g�����v�Z���鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
	float				mOutLineStrength;			// �A�E�g���C������

	Model*				mModel;

	bool				mIsDrawShadow = false;
	Shader*				mShadowMapShader;
	ShadowMap*			mShadowMap;

	MeshRender(void);
	~MeshRender(void);

	void start(void);
	void update(void);
	void drawImGui(void);
	void drawGameObject(void);
	void drawShadowMap(void);
};

#endif // !_MESH_RENDER_H_
