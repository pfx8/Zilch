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
MeshRender::MeshRender(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
MeshRender::~MeshRender(void)
{
	RELEASE_CLASS_POINT(this->mShadowMap);
}

//*****************************************************************************
//
// ������
//
//*****************************************************************************
void MeshRender::start(void)
{
	// �f�t�H���g�V�F�[�_�[���擾
	this->mCurrentShader = this->mParentGameObject->mParentScene->mCurrentShader;

	// �V���h�[�}�b�v
	if (this->mIsDrawShadow == true)
	{
		// ���C�g�ʒu���擾
		D3DXVECTOR3 pos = this->mParentGameObject->mParentScene->getGameObject(L"Light")->getComponent<Light>()->mLightPos;
		this->mShadowMap = new ShadowMap(this->mShadowMapShader, pos);
	}

	// �A�E�g���C��������
	this->mOutlineFactor = 0.2f;
	this->mOutlineStrength = 0.01f;
	this->mOutlineColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void MeshRender::update(void)
{
	// �V���h�[�}�b�v
	if (this->mIsDrawShadow == true)
	{
		this->mShadowMap->update();
	}

	// �A�j���[�V�������X�V
	float deltaTime = getGameTimes()->mDeltaTime;
	this->mModel->updateAnimation(deltaTime);
}

//*****************************************************************************
//
// �V���h�E�}�b�v��`��
//
//*****************************************************************************
void MeshRender::drawShadowMap(void)
{
	this->mShadowMap->draw(this->mModel);
}

//*****************************************************************************
//
// ���b�V���`��
//
//*****************************************************************************
void MeshRender::drawGameObject(void)
{
	// ���C�g�����V�F�[�_�[�ɓn��
	Light* light = this->mParentGameObject->mParentScene->getGameObject(L"Light")->getComponent<Light>();

	// ���L�v���p�e�B
	this->mCurrentShader->mEffect->SetInt("lightType", light->mLightType);
	this->mCurrentShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));
	this->mCurrentShader->mEffect->SetFloat("lightStrength", light->mLightStrength);
	this->mCurrentShader->mEffect->SetFloat("lightAmbient", light->mLightAmbient);
	this->mCurrentShader->mEffect->SetFloat("lightDiffuse", light->mLightDiffuse);
	this->mCurrentShader->mEffect->SetFloat("lightSpecular", light->mLightSpecular);

	// ���C�g�^�C�v�ɂ���ăv���p�e�B���V�F�[�_�[�ɓn��
	switch (light->mLightType)
	{
	case LT_direction:
		this->mCurrentShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		this->mCurrentShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// �����l�����ϐ����V�F�[�_�[�ɓn��
		this->mCurrentShader->mEffect->SetFloat("lightConstant", light->mPointLight.constant);
		this->mCurrentShader->mEffect->SetFloat("lightLinear", light->mPointLight.linear);
		this->mCurrentShader->mEffect->SetFloat("lightQuadratic", light->mPointLight.quadratic);

		break;
	case LT_spot:
		this->mCurrentShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));
		this->mCurrentShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));
		this->mCurrentShader->mEffect->SetFloat("cutOff", light->mSpotLight.cutOff);

		break;
	}

	// ���f�������V�F�[�_�[�ɓn��
	Transform* trans = this->mParentGameObject->getComponent<Transform>();
	this->mCurrentShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mCurrentShader->mEffect->SetMatrix("norMatrix", &trans->mNormalMatrix);

	// �J�����������V�F�[�_�[�ɓn��
	Camera* camera = this->mParentGameObject->mParentScene->mCurrentCamera;
	this->mCurrentShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mCurrentShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);
	this->mCurrentShader->mEffect->SetValue("cameraPos", &camera->mCameraPos, sizeof(camera->mCameraPos));

	// �����_�����O���[�h���V�F�[�_�[�ɓn��
	this->mCurrentShader->mEffect->SetInt("renderingMode", this->mCurrentShader->mRenderingMode);

	// �J���[�����v���[�h���V�F�[�_�[�ɓn��
	this->mCurrentShader->mEffect->SetInt("colorRampType", this->mCurrentShader->mColorRampType);

	// �Z�O�����g�l���V�F�[�_�[�ɓn��
	if (this->mCurrentShader->mColorRampType == CR_CONSTANT)
	{
		this->mCurrentShader->mEffect->SetValue("colorRampSegment", &this->mCurrentShader->mColorRampSegment, sizeof(this->mCurrentShader->mColorRampSegment));
	}

	// �A�E�g���C���ݒ���V�F�[�_�[�ɓn��
	this->mCurrentShader->mEffect->SetFloat("outlineFactor", this->mOutlineFactor); 
	this->mCurrentShader->mEffect->SetFloat("outlineStrength", this->mOutlineStrength);
	this->mCurrentShader->mEffect->SetValue("outlineColor", &this->mOutlineColor, sizeof(this->mOutlineColor));

	// ���f����`��
	this->mModel->drawModel(this->mCurrentShader, this->mIsDrawOutline);
}

//*****************************************************************************
//
// ImGui��MeshRender�̃f�[�^���o��
//
//*****************************************************************************
void MeshRender::drawImGui(void)
{
	// �A�E�g���C��
	ImGui::Checkbox(u8"�A�E�g���C��", &this->mIsDrawOutline);
	if (this->mIsDrawOutline)
	{
		ImGui::TextUnformatted(u8"�A�E�g���C������");
		ImGui::DragFloat(u8"factor", &this->mOutlineFactor, 0.05f, -2.0f, 2.0f);
		ImGui::TextUnformatted(u8"�A�E�g���C������");
		ImGui::InputFloat(u8"strength", &this->mOutlineStrength);
		ImGui::TextUnformatted(u8"�A�E�g���C���J���[");
		ImGui::ColorEdit4(u8"���C�g�J���[", this->mOutlineColor, ImGuiColorEditFlags_RGB);
	}

	if (ImGui::TreeNode(u8"���f��"))
	{
		// ���f�����
		string path = wstringToString(this->mModel->mPath);
		ImGui::Text(u8"�p�X : %s", path.c_str());
		ImGui::Text(u8"���b�V���� : %d", this->mModel->mModelInfo.numMeshes);
		ImGui::Text(u8"���� : %d", this->mModel->mBones.size());
		ImGui::Text(u8"�}�e���A���� : %d", this->mModel->mModelInfo.numMaterials);
		ImGui::Text(u8"�A�j���[�V������ : %d", this->mModel->mModelInfo.numAnimations);
		ImGui::Separator();

		// ���b�V�����
		if (ImGui::TreeNode(u8"���b�V��"))
		{
			unsigned int ID1s = 0;
			for (auto it1 : this->mModel->mMeshes)
			{
				ImGui::PushID(ID1s);
				string name = wstringToString((wstring const)it1->mName);
				if (ImGui::TreeNode("mesh", u8"<Mesh> : %s", name.c_str()))
				{
					ImGui::Text(u8"���_�� : %d", it1->mMeshInfo.numVertices);
					ImGui::Text(u8"�|���S���� : %d", it1->mMeshInfo.numFaces);
					ImGui::Separator();
					
					for (auto it2 : it1->mMaterials)
					{
						// material
						string name2 = wstringToString(it2->mName.c_str());
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

						// diffuse
						if (it2->mTextures.size() == 1)
						{
							string path1 = wstringToString(it2->mTextures.at(0)->mPath);
							strcpy(this->mTexPathTemp, path1.c_str());
							string name3 = wstringToString(it2->mTextures.at(0)->mName);

							ImGui::PushID(1);
							if (ImGui::TreeNode("texture1", u8"<Texture><Diffuse> : %s", name3.c_str()))
							{
								// �e�N�X�`����ImGui�ŏo��
								ImGui::Image((void*)it2->mTextures.at(0)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"�e�N�X�`���p�X", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// �V�����e�N�X�`���p�X��ۑ�
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(0)->mPath = str;

								// ���͂����p�X�ɂ���ăe�N�X�`���������[�h
								if (ImGui::Button(u8"�����[�h"))
								{
									it2->mTextures.at(0)->loadingTexture(str);
								}

								ImGui::TreePop();
							}
							ImGui::PopID();
						}

						// height
						if (it2->mTextures.size() == 3)
						{
							string path2 = wstringToString(it2->mTextures.at(1)->mPath);
							strcpy(this->mTexPathTemp, path2.c_str());
							string name4 = wstringToString(it2->mTextures.at(1)->mName);

							ImGui::PushID(2);
							if (ImGui::TreeNode("texture2", u8"<Texture><Height> : %s", name4.c_str()))
							{
								// �e�N�X�`����ImGui�ŏo��
								ImGui::Image((void*)it2->mTextures.at(1)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"�e�N�X�`���p�X", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// �V�����e�N�X�`���p�X��ۑ�
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(1)->mPath = str;

								// ���͂����p�X�ɂ���ăe�N�X�`���������[�h
								if (ImGui::Button(u8"�����[�h"))
								{
									it2->mTextures.at(1)->loadingTexture(str);
								}

								ImGui::TreePop();
							}
							ImGui::PopID();
						}

						// specular
						if (it2->mTextures.size() == 3)
						{
							string path3 = wstringToString(it2->mTextures.at(2)->mPath);
							strcpy(this->mTexPathTemp, path3.c_str());
							string name5 = wstringToString(it2->mTextures.at(2)->mName);

							ImGui::PushID(3);
							if (ImGui::TreeNode("texture3", u8"<Texture><Specular> : %s", name5.c_str()))
							{
								// �e�N�X�`����ImGui�ŏo��
								ImGui::Image((void*)it2->mTextures.at(2)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"�e�N�X�`���p�X", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// �V�����e�N�X�`���p�X��ۑ�
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(2)->mPath = str;

								// ���͂����p�X�ɂ���ăe�N�X�`���������[�h
								if (ImGui::Button(u8"�����[�h"))
								{
									it2->mTextures.at(2)->loadingTexture(str);
								}

								ImGui::TreePop();
							}
							ImGui::PopID();
						}
					}

					ImGui::TreePop();
				}

				ID1s++;
				ImGui::PopID();
			}

			ImGui::TreePop();
		}

		// �A�j���[�V�������
		if (ImGui::TreeNode(u8"�A�j���[�V����"))
		{
			unsigned int ID = 0;
			for (auto it : this->mModel->mAnimationes)
			{
				ImGui::PushID(ID);
				string name = wstringToString((wstring const)it->mName);
				if (ImGui::TreeNode("animation", u8"<Animation> : %s", name.c_str()))
				{
					ImGui::Text(u8"����(Max : %f)", it->mDuration / it->mTicksPerSecond);
					ImGui::SliderFloat("times", &it->mLastStartTime, 0.0f, it->mDuration / it->mTicksPerSecond);

					unsigned int ID2 = 0;
					for (auto it2 : it->mAnimationChannels)
					{
						ImGui::PushID(ID2);
						string name = wstringToString((wstring const)it2->mNodeName);
						if (ImGui::TreeNode(u8"<KeyFrame> : %s", name.c_str()))
						{
							ImGui::Text(u8"Pos %d", it2->mPosKeys.size());
							ImGui::Text(u8"Scl %d", it2->mSclKeys.size());
							ImGui::Text(u8"Rot %d", it2->mRotkeys.size());

							ImGui::TreePop();
						}

						ID2++;
						ImGui::PopID();
					}

					ImGui::TreePop();
				}

				ID++;
				ImGui::PopID();
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}