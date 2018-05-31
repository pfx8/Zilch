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
	Shader*				mShader;					// �`�悷��p�̃V�F�[�_�[(by�V�[��)

	char				mModelPathTemp[MAX_PATH];	// ���f���p�X
	char				mTexPathTemp[MAX_PATH];		// �e�N�X�`���p�X

	void start();									// ������
	void update();									// �X�V

public:
	bool				mIsOutline = false;			// �A�E�g���C���`�F�b�N
	float				mOutLineFactor;				// �A�E�g���C���x�N�g�����v�Z���鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
	float				mOutLineStrength;			// �A�E�g���C������

	bool				mIsDrawShadow = false;		// �V���h�E�`�F�b�N
	Model*				mModel;						// �`�悷�郂�f��
	Shader*				mShadowMapShader;			// �V���h�E�}�b�v�V�F�[�_�[
	ShadowMap*			mShadowMap;					// �V���h�E�}�b�v

	MeshRender();
	~MeshRender();

	void draw();									// ���b�V����`��
	void drawShadowMap();							// �V���h�E�}�b�v��`��
	void drawImGui();								// ImGui��MeshRender�̃f�[�^���o��
};

#endif // !_MESH_RENDER_H_
