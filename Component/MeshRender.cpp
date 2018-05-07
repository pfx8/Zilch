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
	// �f�t�H���g�V�F�[�_�[���擾
	this->mShader = this->mGameObject->mScene->mShader;

	// �V���h�[�}�b�v
	if (this->mIsDrawShadow == true)
	{
		// ���C�g�ʒu���擾
		D3DXVECTOR3 pos = this->mGameObject->mScene->getGameObject("light")->getComponent<Light>()->mLightPos;
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
	// ���C�g���擾
	Light* light = this->mGameObject->mScene->getGameObject("light")->getComponent<Light>();
	// ���C�g�^�C�v���V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetInt("lightType", light->mLightType);

	// ���C�g�^�C�v�ɂ���ăV�F�[�_�[�ɕϐ���n��
	switch (light->mLightType)
	{
	case LT_direction:
		// ���C�g�J���[���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// ���C�g�������V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		// ���C�g�ʒu���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// ���C�g�J���[���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// �����l�����ϐ����V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetFloat("lightConstant", light->mPointLight.constant);
		this->mShader->mEffect->SetFloat("lightLinear", light->mPointLight.linear);
		this->mShader->mEffect->SetFloat("lightQuadratic", light->mPointLight.quadratic);

		break;
	case LT_spot:
		// ���C�g�ʒu���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// ���C�g�J���[���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// ���C�g�������V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		// �R�T�C���l���V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetFloat("cutOff", light->mSpotLight.cutOff);

		break;
	}

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
	this->mModel->drawModel(this->mShader);
}

//*****************************************************************************
//
// ImGui��MeshRender�̃f�[�^���o��
//
//*****************************************************************************
void MeshRender::drawImGui()
{
	if (ImGui::TreeNode(u8"���f��"))
	{
		// ���b�V�����
		for (auto it : this->mModel->mMeshes)
		{
			ImGui::Text("<Mesh> : %s", it->mName.c_str());

			// material
			for (auto it1 : it->mMaterials)
			{
				ImGui::Text("  <Material> : %s", it1->mName.c_str());

				// texture
				for (auto it2 : it1->mTextures)
				{
					ImGui::Text("    <Texture>: %s", it2->mName.c_str());
				}
			}
		}

		// �����
		if (this->mModel->mMeshType == MT_withBone)
		{
			if (ImGui::TreeNode(u8"�{�[��"))
			{
				unsigned int level = 0;
				this->mModel->traverseNode(*(this->mModel->mAnimationes.at(0)->mNode.end() - 1), level);

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}