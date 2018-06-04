//*****************************************************************************
//
// 変換処理 [Transform.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "MeshRender.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
MeshRender::MeshRender(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
MeshRender::~MeshRender(void)
{
	RELEASE_CLASS_POINT(this->mShadowMap);
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void MeshRender::start(void)
{
	// デフォルトシェーダーを取得
	this->mCurrentShader = this->mParentGameObject->mParentScene->mCurrentShader;

	// シャドーマップ
	if (this->mIsDrawShadow == true)
	{
		// ライト位置を取得
		D3DXVECTOR3 pos = this->mParentGameObject->mParentScene->getGameObject(L"Light")->getComponent<Light>()->mLightPos;
		this->mShadowMap = new ShadowMap(this->mShadowMapShader, pos);
	}

	// アウトライン初期化
	this->mOutlineFactor = 0.2f;
	this->mOutlineStrength = 0.01f;
	this->mOutlineColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void MeshRender::update(void)
{
	// シャドーマップ
	if (this->mIsDrawShadow == true)
	{
		this->mShadowMap->update();
	}

	// アニメーションを更新
	float deltaTime = getGameTimes()->mDeltaTime;
	this->mModel->updateAnimation(deltaTime);
}

//*****************************************************************************
//
// シャドウマップを描画
//
//*****************************************************************************
void MeshRender::drawShadowMap(void)
{
	this->mShadowMap->draw(this->mModel);
}

//*****************************************************************************
//
// メッシュ描画
//
//*****************************************************************************
void MeshRender::drawGameObject(void)
{
	// ライト情報をシェーダーに渡す
	Light* light = this->mParentGameObject->mParentScene->getGameObject(L"Light")->getComponent<Light>();

	// 共有プロパティ
	this->mCurrentShader->mEffect->SetInt("lightType", light->mLightType);
	this->mCurrentShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));
	this->mCurrentShader->mEffect->SetFloat("lightStrength", light->mLightStrength);
	this->mCurrentShader->mEffect->SetFloat("lightAmbient", light->mLightAmbient);
	this->mCurrentShader->mEffect->SetFloat("lightDiffuse", light->mLightDiffuse);
	this->mCurrentShader->mEffect->SetFloat("lightSpecular", light->mLightSpecular);

	// ライトタイプによってプロパティをシェーダーに渡す
	switch (light->mLightType)
	{
	case LT_direction:
		this->mCurrentShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		this->mCurrentShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// 減衰値公式変数をシェーダーに渡す
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

	// モデル情報をシェーダーに渡す
	Transform* trans = this->mParentGameObject->getComponent<Transform>();
	this->mCurrentShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mCurrentShader->mEffect->SetMatrix("norMatrix", &trans->mNormalMatrix);

	// カメラ情報情報をシェーダーに渡す
	Camera* camera = this->mParentGameObject->mParentScene->mCurrentCamera;
	this->mCurrentShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mCurrentShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);
	this->mCurrentShader->mEffect->SetValue("cameraPos", &camera->mCameraPos, sizeof(camera->mCameraPos));

	// レンダリングモードをシェーダーに渡す
	this->mCurrentShader->mEffect->SetInt("renderingMode", this->mCurrentShader->mRenderingMode);

	// カラーランプモードをシェーダーに渡す
	this->mCurrentShader->mEffect->SetInt("colorRampType", this->mCurrentShader->mColorRampType);

	// セグメント値をシェーダーに渡す
	if (this->mCurrentShader->mColorRampType == CR_CONSTANT)
	{
		this->mCurrentShader->mEffect->SetValue("colorRampSegment", &this->mCurrentShader->mColorRampSegment, sizeof(this->mCurrentShader->mColorRampSegment));
	}

	// アウトライン設定をシェーダーに渡す
	this->mCurrentShader->mEffect->SetFloat("outlineFactor", this->mOutlineFactor); 
	this->mCurrentShader->mEffect->SetFloat("outlineStrength", this->mOutlineStrength);
	this->mCurrentShader->mEffect->SetValue("outlineColor", &this->mOutlineColor, sizeof(this->mOutlineColor));

	// モデルを描画
	this->mModel->drawModel(this->mCurrentShader, this->mIsDrawOutline);
}

//*****************************************************************************
//
// ImGuiでMeshRenderのデータを出す
//
//*****************************************************************************
void MeshRender::drawImGui(void)
{
	// アウトライン
	ImGui::Checkbox(u8"アウトライン", &this->mIsDrawOutline);
	if (this->mIsDrawOutline)
	{
		ImGui::TextUnformatted(u8"アウトライン因数");
		ImGui::DragFloat(u8"factor", &this->mOutlineFactor, 0.05f, -2.0f, 2.0f);
		ImGui::TextUnformatted(u8"アウトライン太さ");
		ImGui::InputFloat(u8"strength", &this->mOutlineStrength);
		ImGui::TextUnformatted(u8"アウトラインカラー");
		ImGui::ColorEdit4(u8"ライトカラー", this->mOutlineColor, ImGuiColorEditFlags_RGB);
	}

	if (ImGui::TreeNode(u8"モデル"))
	{
		// モデル情報
		string path = wstringToString(this->mModel->mPath);
		ImGui::Text(u8"パス : %s", path.c_str());
		ImGui::Text(u8"メッシュ数 : %d", this->mModel->mModelInfo.numMeshes);
		ImGui::Text(u8"骨数 : %d", this->mModel->mBones.size());
		ImGui::Text(u8"マテリアル数 : %d", this->mModel->mModelInfo.numMaterials);
		ImGui::Text(u8"アニメーション数 : %d", this->mModel->mModelInfo.numAnimations);
		ImGui::Separator();

		// メッシュ情報
		if (ImGui::TreeNode(u8"メッシュ"))
		{
			unsigned int ID1s = 0;
			for (auto it1 : this->mModel->mMeshes)
			{
				ImGui::PushID(ID1s);
				string name = wstringToString((wstring const)it1->mName);
				if (ImGui::TreeNode("mesh", u8"<Mesh> : %s", name.c_str()))
				{
					ImGui::Text(u8"頂点数 : %d", it1->mMeshInfo.numVertices);
					ImGui::Text(u8"ポリゴン数 : %d", it1->mMeshInfo.numFaces);
					ImGui::Separator();
					
					for (auto it2 : it1->mMaterials)
					{
						// material
						string name2 = wstringToString(it2->mName.c_str());
						if (ImGui::TreeNode("material", u8"<Material> : %s", name2.c_str()))
						{
							ImGui::PushID(1);
							ImGui::TextUnformatted(u8"アンビエント");
							ImGui::SliderFloat(u8"R", &it2->mAmbient.x, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"G", &it2->mAmbient.y, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"B", &it2->mAmbient.z, 0.0f, 1.0f);
							ImGui::PopID();

							ImGui::PushID(2);
							ImGui::TextUnformatted(u8"ディフューズ");
							ImGui::SliderFloat(u8"R", &it2->mDiffuse.x, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"G", &it2->mDiffuse.y, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"B", &it2->mDiffuse.z, 0.0f, 1.0f);
							ImGui::PopID();

							ImGui::PushID(3);
							ImGui::TextUnformatted(u8"スペキュラー");
							ImGui::SliderFloat(u8"R", &it2->mSpecular.x, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"G", &it2->mSpecular.y, 0.0f, 1.0f);
							ImGui::SliderFloat(u8"B", &it2->mSpecular.z, 0.0f, 1.0f);
							ImGui::PopID();

							ImGui::Text(u8"光沢");
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
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(0)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(0)->mPath = str;

								// 入力したパスによってテクスチャをリロード
								if (ImGui::Button(u8"リロード"))
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
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(1)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(1)->mPath = str;

								// 入力したパスによってテクスチャをリロード
								if (ImGui::Button(u8"リロード"))
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
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(2)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringToWstring(this->mTexPathTemp);
								it2->mTextures.at(2)->mPath = str;

								// 入力したパスによってテクスチャをリロード
								if (ImGui::Button(u8"リロード"))
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

		// アニメーション情報
		if (ImGui::TreeNode(u8"アニメーション"))
		{
			unsigned int ID = 0;
			for (auto it : this->mModel->mAnimationes)
			{
				ImGui::PushID(ID);
				string name = wstringToString((wstring const)it->mName);
				if (ImGui::TreeNode("animation", u8"<Animation> : %s", name.c_str()))
				{
					ImGui::Text(u8"時間(Max : %f)", it->mDuration / it->mTicksPerSecond);
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