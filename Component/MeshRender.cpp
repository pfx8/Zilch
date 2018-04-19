//*****************************************************************************
//
// �ϊ����� [Transform.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "MeshRender.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
MeshRender::MeshRender()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
MeshRender::~MeshRender()
{

}

//*****************************************************************************
//
// �h���[
//
//*****************************************************************************
void MeshRender::draw()
{
	// ���f���̃��[���h�ϊ��s����擾
	Transform* trans = this->mGameObject->getComponent<Transform>("trans");
	// ���f���̃��[���h�ϊ��s����V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);

	// �J���������擾
	Camera* camera = this->mGameObject->mScene->getGameObject("mainCamera")->getComponent<Camera>("camera");
	// �J�����̍s����V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	mModel->draw(this->mShader, trans, camera);
}
