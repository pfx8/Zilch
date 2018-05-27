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
		D3DXVECTOR3 pos = this->mGameObject->mScene->getGameObject(L"light")->getComponent<Light>()->mLightPos;
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

	// �A�j���[�V�������X�V
	float deltaTime {getGameTimes()->mDeltaTime};
	this->mModel->updateAnimation(deltaTime);
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
	// ���C�g�����V�F�[�_�[�ɓn��
	Light* light = this->mGameObject->mScene->getGameObject(L"light")->getComponent<Light>();

	// ���L�v���p�e�B
	this->mShader->mEffect->SetInt("lightType", light->mLightType);
	this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));
	this->mShader->mEffect->SetFloat("lightAmbient", light->mLightAmbient);
	this->mShader->mEffect->SetFloat("lightDiffuse", light->mLightDiffuse);
	this->mShader->mEffect->SetFloat("lightSpecular", light->mLightSpecular);

	// ���C�g�^�C�v�ɂ���ăv���p�e�B���V�F�[�_�[�ɓn��
	switch (light->mLightType)
	{
	case LT_direction:
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// �����l�����ϐ����V�F�[�_�[�ɓn��
		this->mShader->mEffect->SetFloat("lightConstant", light->mPointLight.constant);
		this->mShader->mEffect->SetFloat("lightLinear", light->mPointLight.linear);
		this->mShader->mEffect->SetFloat("lightQuadratic", light->mPointLight.quadratic);

		break;
	case LT_spot:
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));
		this->mShader->mEffect->SetFloat("cutOff", light->mSpotLight.cutOff);

		break;
	}

	// ���f�������V�F�[�_�[�ɓn��
	Transform* trans = this->mGameObject->getComponent<Transform>();
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mShader->mEffect->SetMatrix("norMatrix", &trans->mNormalMatrix);

	// �J�����������V�F�[�_�[�ɓn��
	Camera* camera = this->mGameObject->mScene->mCurrentCamera;
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);
	this->mShader->mEffect->SetValue("cameraPos", &camera->mCameraPos, sizeof(camera->mCameraPos));

	// �����_�����O���[�h���V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetInt("renderingMode", this->mShader->mRenderingMode);

	// �J���[�����v���[�h���V�F�[�_�[�ɓn��
	this->mShader->mEffect->SetInt("colorRamp", this->mShader->mColorRamp);
	// �Z�O�����g�l���V�F�[�_�[�ɓn��
	if (this->mShader->mColorRamp == CR_CONSTANT)
	{
		this->mShader->mEffect->SetValue("colorRampSegment", &this->mShader->mColorRampSegment, sizeof(this->mShader->mColorRampSegment));
	}

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
		// ���f�����
		string path = wstringUnicodeToUTF8(this->mModel->mPath);
		ImGui::Text(u8"�p�X : %s", path.c_str());
		ImGui::Text(u8"���b�V���� : %d", this->mModel->mModelInfo.numMeshes);
		ImGui::Text(u8"���� : %d", this->mModel->mBones.size());
		ImGui::Text(u8"�}�e���A���� : %d", this->mModel->mModelInfo.numMaterials);
		//ImGui::Text(u8"�A�j���[�V������:%d", );
		ImGui::Separator();

		// ���b�V�����
		unsigned int ID1s = 0;
		for (auto it1 : this->mModel->mMeshes)
		{
			ImGui::PushID(ID1s);
			string name = wstringUnicodeToUTF8((wstring const)it1->mName);
			if (ImGui::TreeNode("mesh", u8"<Mesh> : %s", name.c_str()))
			{
				ImGui::Text(u8"���_�� : %d", it1->mMeshInfo.numVertices);
				ImGui::Text(u8"�|���S���� : %d", it1->mMeshInfo.numFaces);
				ImGui::Separator();

				// material
				for (auto it2 : it1->mMaterials)
				{
					string name2 = wstringUnicodeToUTF8(it2->mName.c_str());
					if (ImGui::TreeNode("material", u8"<Material> : %s", name2.c_str()))
					{
						ImGui::PushID(1);
						ImGui::TextUnformatted(u8"�A���r�G���g");
						ImGui::SliderFloat(u8"R", &it2->mAmbient.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mAmbient.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mAmbient.z, 0.0f, 1.0f);
						ImGui::PopID();

						ImGui::PushID(2);
						ImGui::TextUnformatted(u8"�f�B�t���[�Y");
						ImGui::SliderFloat(u8"R", &it2->mDiffuse.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mDiffuse.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mDiffuse.z, 0.0f, 1.0f);
						ImGui::PopID();

						ImGui::PushID(3);
						ImGui::TextUnformatted(u8"�X�y�L�����[");
						ImGui::SliderFloat(u8"R", &it2->mSpecular.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mSpecular.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mSpecular.z, 0.0f, 1.0f);
						ImGui::PopID();

						ImGui::Text(u8"����");
						ImGui::InputFloat(u8"S", &it2->mShininess);

						ImGui::TreePop();
					}

					// texture
					unsigned int ID2s = 0;
					for (auto it3 : it2->mTextures)
					{
						// �e�N�X�`���p�X�Ɩ��O
						string path1 = wstringUnicodeToUTF8(it3->mPath);
						strcpy(this->mTexPathTemp, path1.c_str());
						string name3 = wstringUnicodeToUTF8(it3->mName);

						ImGui::PushID(ID2s);
						if (ImGui::TreeNode("texture", u8"<Texture> : %s", name3.c_str()))
						{
							// �e�N�X�`����ImGui�ŏo��
							ImGui::Image((void*)it3->mTex, ImVec2(150, 150));
							ImGui::InputText(u8"�e�N�X�`���p�X", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

							// �V�����e�N�X�`���p�X��ۑ�
							wstring str = stringUTF8ToUnicode(this->mTexPathTemp);
							it3->mPath = str;

							// ���͂����p�X�ɂ���ăe�N�X�`���������[�h
							if (ImGui::Button(u8"�����[�h"))
							{
								it3->loadingTexture(str);
							}

							ImGui::TreePop();
						}

						ID2s++;
						ImGui::PopID();
					}
				}

				ImGui::TreePop();
			}

			ID1s++;
			ImGui::PopID();
		}

		// �����
		/*if (this->mModel->mMeshType == MT_withBone)
		{
			if (ImGui::TreeNode(u8"�{�[��"))
			{
				unsigned int level = 0;
				this->mModel->traverseNode(*(this->mModel->mAnimationes.at(0)->mNode.end() - 1), level);

				ImGui::TreePop();
			}
		}*/

		ImGui::TreePop();
	}
}