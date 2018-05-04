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
// ������
//
//*****************************************************************************
void MeshRender::start()
{
	// �V�[�����烌���_�����O�V�F�[�_�[���擾
	this->mShader = this->mGameObject->mScene->mShader;

	// �V���h�[�}�b�v
	if (this->mIsDrawShadow == true)
	{
		// ���C�g�ʒu���擾
		D3DXVECTOR3 pos = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mLightPos;
		this->mShadowMap = new ShadowMap(this->mShadowMapShader, pos);
	}
}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void MeshRender::update()
{
	// �V���h�[�}�b�v
	if (this->mIsDrawShadow == true)
	{
		this->mShadowMap->update();
	}

}

//*****************************************************************************
//
// �V���h�E�}�b�v��`��
//
//*****************************************************************************
void MeshRender::drawShadowMap()
{
	this->mShadowMap->draw(this->mModel);
}

//*****************************************************************************
//
// ���b�V���`��
//
//*****************************************************************************
void MeshRender::draw()
{
	// ���C�g��ݒ�
	D3DXVECTOR3 lightPos = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mLightPos;
	D3DXVECTOR4 lightColor = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mLightColor;
	float constant = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mConstant;
	float linear = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mLinear;
	float quadratic = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mQuadratic;

	this->mShader->mEffect->SetValue("lightPos", &lightPos, sizeof(lightPos));
	this->mShader->mEffect->SetValue("lightColor", &lightColor, sizeof(lightColor));
	this->mShader->mEffect->SetFloat("lightConstant", constant);
	this->mShader->mEffect->SetFloat("lightLinear", linear);
	this->mShader->mEffect->SetFloat("lightQuadratic", quadratic);

	// ���f���̃��[���h�ϊ��s����擾
	Transform* trans = this->mGameObject->getComponent<Transform>();
	// ���f���̃��[���h�ϊ��s��Ɖ�]�s����V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mShader->mEffect->SetMatrix("rotMatrix", &trans->mRotMatrix);

	// �J���������擾
	Camera* camera = this->mGameObject->mScene->getGameObject("mainCamera")->getComponent<Camera>();
	// �J�����̍s����V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	// �����_�����O���[�h���V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetInt("renderType", this->mShader->mRenderType);

	// ���f����`��
	this->mModel->draw(this->mShader, trans, camera);
}