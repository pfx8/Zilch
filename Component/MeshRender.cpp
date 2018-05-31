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
MeshRender::MeshRender()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
MeshRender::~MeshRender()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void MeshRender::start()
{
	// デフォルトシェーダーを取得
	this->mShader = this->mGameObject->mScene->mShader;

	// シャドーマップ
	if (this->mIsDrawShadow == true)
	{
		// ライト位置を取得
		D3DXVECTOR3 pos = this->mGameObject->mScene->getGameObject(L"light")->getComponent<Light>()->mLightPos;
		this->mShadowMap = new ShadowMap(this->mShadowMapShader, pos);
	}
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void MeshRender::update()
{
	// シャドーマップ
	if (this->mIsDrawShadow == true)
	{
		this->mShadowMap->update();
	}

	// アニメーションを更新
	float deltaTime {getGameTimes()->mDeltaTime};
	this->mModel->updateAnimation(deltaTime);
}

//*****************************************************************************
//
// シャドウマップを描画
//
//*****************************************************************************
void MeshRender::drawShadowMap()
{
	this->mShadowMap->draw(this->mModel);
}

//*****************************************************************************
//
// メッシュ描画
//
//*****************************************************************************
void MeshRender::draw()
{
	// ライト情報をシェーダーに渡す
	Light* light = this->mGameObject->mScene->getGameObject(L"light")->getComponent<Light>();

	// 共有プロパティ
	this->mShader->mEffect->SetInt("lightType", light->mLightType);
	this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));
	this->mShader->mEffect->SetFloat("lightStrength", light->mLightStrength);
	this->mShader->mEffect->SetFloat("lightAmbient", light->mLightAmbient);
	this->mShader->mEffect->SetFloat("lightDiffuse", light->mLightDiffuse);
	this->mShader->mEffect->SetFloat("lightSpecular", light->mLightSpecular);

	// ライトタイプによってプロパティをシェーダーに渡す
	switch (light->mLightType)
	{
	case LT_direction:
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// 減衰値公式変数をシェーダーに渡す
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

	// モデル情報をシェーダーに渡す
	Transform* trans = this->mGameObject->getComponent<Transform>();
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mShader->mEffect->SetMatrix("norMatrix", &trans->mNormalMatrix);

	// カメラ情報情報をシェーダーに渡す
	Camera* camera = this->mGameObject->mScene->mCurrentCamera;
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);
	this->mShader->mEffect->SetValue("cameraPos", &camera->mCameraPos, sizeof(camera->mCameraPos));

	// レンダリングモードをシェーダーに渡す
	this->mShader->mEffect->SetInt("renderingMode", this->mShader->mRenderingMode);

	// カラーランプモードをシェーダーに渡す
	this->mShader->mEffect->SetInt("colorRampType", this->mShader->mColorRampType);

	// セグメント値をシェーダーに渡す
	if (this->mShader->mColorRampType == CR_CONSTANT)
	{
		this->mShader->mEffect->SetValue("colorRampSegment", &this->mShader->mColorRampSegment, sizeof(this->mShader->mColorRampSegment));
	}

	// モデルを描画
	this->mModel->drawModel(this->mShader, this->mIsOutline);
}

//*****************************************************************************
//
// ImGuiでMeshRenderのデータを出す
//
//*****************************************************************************
void MeshRender::drawImGui()
{
	ImGui::Checkbox(u8"アウトライン", &this->mIsOutline);

	if (ImGui::TreeNode(u8"モデル"))
	{
		// モデル情報
		string path = wstringUnicodeToUTF8(this->mModel->mPath);
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
				string name = wstringUnicodeToUTF8((wstring const)it1->mName);
				//CollapsingHeader
				if (ImGui::TreeNode("mesh", u8"<Mesh> : %s", name.c_str()))
				{
					ImGui::Text(u8"頂点数 : %d", it1->mMeshInfo.numVertices);
					ImGui::Text(u8"ポリゴン数 : %d", it1->mMeshInfo.numFaces);
					ImGui::Separator();
					
					for (auto it2 : it1->mMaterials)
					{
						// material
						string name2 = wstringUnicodeToUTF8(it2->mName.c_str());
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
							string path1 = wstringUnicodeToUTF8(it2->mTextures.at(0)->mPath);
							strcpy(this->mTexPathTemp, path1.c_str());
							string name3 = wstringUnicodeToUTF8(it2->mTextures.at(0)->mName);

							ImGui::PushID(1);
							if (ImGui::TreeNode("texture1", u8"<Texture><Diffuse> : %s", name3.c_str()))
							{
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(0)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringUTF8ToUnicode(this->mTexPathTemp);
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
							string path2 = wstringUnicodeToUTF8(it2->mTextures.at(1)->mPath);
							strcpy(this->mTexPathTemp, path2.c_str());
							string name4 = wstringUnicodeToUTF8(it2->mTextures.at(1)->mName);

							ImGui::PushID(2);
							if (ImGui::TreeNode("texture2", u8"<Texture><Height> : %s", name4.c_str()))
							{
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(1)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringUTF8ToUnicode(this->mTexPathTemp);
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
							string path3 = wstringUnicodeToUTF8(it2->mTextures.at(2)->mPath);
							strcpy(this->mTexPathTemp, path3.c_str());
							string name5 = wstringUnicodeToUTF8(it2->mTextures.at(2)->mName);

							ImGui::PushID(3);
							if (ImGui::TreeNode("texture3", u8"<Texture><Specular> : %s", name5.c_str()))
							{
								// テクスチャをImGuiで出す
								ImGui::Image((void*)it2->mTextures.at(2)->mTex, ImVec2(150, 150));
								ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

								// 新しいテクスチャパスを保存
								wstring str = stringUTF8ToUnicode(this->mTexPathTemp);
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
				string name = wstringUnicodeToUTF8((wstring const)it->mName);
				if (ImGui::TreeNode("animation", u8"<Animation> : %s", name.c_str()))
				{
					ImGui::Text(u8"時間(Max : %f)", it->mDuration / it->mTicksPerSecond);
					ImGui::SliderFloat("times", &it->mLastStartTime, 0.0f, it->mDuration / it->mTicksPerSecond);

					unsigned int ID2 = 0;
					for (auto it2 : it->mAnimationChannels)
					{
						ImGui::PushID(ID2);
						string name = wstringUnicodeToUTF8((wstring const)it2->mNodeName);
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
		

		/*if (this->mModel->mMeshType == MT_withBone)
		{
			if (ImGui::TreeNode(u8"ボーン"))
			{
				unsigned int level = 0;
				this->mModel->traverseNode(*(this->mModel->mAnimationes.at(0)->mNode.end() - 1), level);

				ImGui::TreePop();
			}
		}*/

		ImGui::TreePop();
	}
}