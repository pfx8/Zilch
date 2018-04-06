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
#include "../Engine/Engine.h"
#include "../Engine/Shader.h"
#include "../Engine/Model/Model.h"

class MeshRender : public Component
{
private:
	void start();

public:
	GameObject*		mMainCamera;				// �`�悷�邽�ߎg���Ă�J�������K�v
	Model*				mModel;							// �`�悷�郂�f��
	Shader*				mShader;						// �`�悷��p�̃V�F�[�_�[

	MeshRender();
	~MeshRender();

	void draw();
};

#endif // !_MESH_RENDER_H_
