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
	// ライトを取得
	Light* light = this->mGameObject->mScene->getGameObject(L"light")->getComponent<Light>();
	// ライトタイプをシェーダーに渡す
	this->mShader->mEffect->SetInt("lightType", light->mLightType);

	// ライトタイプによってシェーダーに変数を渡す
	switch (light->mLightType)
	{
	case LT_direction:
		// ライトカラーをシェーダーに渡す
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// ライト方向をシェーダーに渡す
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		break;
	case LT_point:
		// ライト位置をシェーダーに渡す
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// ライトカラーをシェーダーに渡す
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// 減衰値公式変数をシェーダーに渡す
		this->mShader->mEffect->SetFloat("lightConstant", light->mPointLight.constant);
		this->mShader->mEffect->SetFloat("lightLinear", light->mPointLight.linear);
		this->mShader->mEffect->SetFloat("lightQuadratic", light->mPointLight.quadratic);

		break;
	case LT_spot:
		// ライト位置をシェーダーに渡す
		this->mShader->mEffect->SetValue("lightPos", &light->mLightPos, sizeof(light->mLightPos));

		// ライトカラーをシェーダーに渡す
		this->mShader->mEffect->SetValue("lightColor", &light->mLightColor, sizeof(light->mLightColor));

		// ライト方向をシェーダーに渡す
		this->mShader->mEffect->SetValue("direction", &light->mDirectionLight.direction, sizeof(light->mDirectionLight.direction));

		// コサイン値をシェーダーに渡す
		this->mShader->mEffect->SetFloat("cutOff", light->mSpotLight.cutOff);

		break;
	}

	// モデルのワールド変換行列を取得
	Transform* trans = this->mGameObject->getComponent<Transform>();
	// モデルのワールド変換行列と回転行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mShader->mEffect->SetMatrix("rotMatrix", &trans->mRotMatrix);

	// カメラ情報を取得
	Camera* camera = this->mGameObject->mScene->mCurrentCamera;
	// カメラの行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);
	this->mShader->mEffect->SetValue("cameraPos", &camera->mCameraPos, sizeof(camera->mCameraPos));

	// レンダリングモードをシェーダーに渡す
	this->mShader->mEffect->SetInt("renderMode", this->mShader->mRenderMode);

	// カラーランプモードをシェーダーに渡す
	this->mShader->mEffect->SetInt("colorRamp", this->mShader->mColorRamp);
	// セグメント値をシェーダーに渡す
	if (this->mShader->mColorRamp == CR_CONSTANT)
	{
		this->mShader->mEffect->SetValue("colorRampSegment", &this->mShader->mColorRampSegment, sizeof(this->mShader->mColorRampSegment));
	}

	// モデルを描画
	this->mModel->drawModel(this->mShader);
}

//*****************************************************************************
//
// ImGuiでMeshRenderのデータを出す
//
//*****************************************************************************
void MeshRender::drawImGui()
{
	if (ImGui::TreeNode(u8"モデル"))
	{
		// モデル情報
		string path = wstringUnicodeToUTF8(this->mModel->mPath);
		ImGui::Text(u8"パス : %s", path.c_str());
		ImGui::Text(u8"メッシュ数 : %d", this->mModel->mModelInfo.numMeshes);
		ImGui::Text(u8"骨数 : %d", this->mModel->mBones.size());
		ImGui::Text(u8"マテリアル数 : %d", this->mModel->mModelInfo.numMaterials);
		//ImGui::Text(u8"アニメーション数:%d", );
		ImGui::Separator();

		unsigned int ID1s = 0;
		for (auto it1 : this->mModel->mMeshes)
		{
			ImGui::PushID(ID1s);
			string name = wstringUnicodeToUTF8((wstring const)it1->mName);
			if (ImGui::TreeNode("mesh", u8"<Mesh> :%s", name.c_str()))
			{
				// メッシュ情報
				ImGui::Text(u8"頂点数 : %d", it1->mMeshInfo.numVertices);
				ImGui::Text(u8"ポリゴン数 : %d", it1->mMeshInfo.numFaces);
				ImGui::Separator();

				// material
				for (auto it2 : it1->mMaterials)
				{
					string name2 = wstringUnicodeToUTF8(it2->mName.c_str());
					ImGui::Text(u8"  <Material> : %s", name2.c_str());

					if (ImGui::TreeNode(u8"マテリアルのプロパティ"))
					{
						ImGui::Text(u8"環境光");
						ImGui::SliderFloat(u8"R", &it2->mAmbient.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mAmbient.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mAmbient.z, 0.0f, 1.0f);

						ImGui::Text(u8"拡散反射光");
						ImGui::SliderFloat(u8"R", &it2->mDiffuse.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mDiffuse.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mDiffuse.z, 0.0f, 1.0f);

						ImGui::Text(u8"鏡面反射光");
						ImGui::SliderFloat(u8"R", &it2->mSpecular.x, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"G", &it2->mSpecular.y, 0.0f, 1.0f);
						ImGui::SliderFloat(u8"B", &it2->mSpecular.z, 0.0f, 1.0f);

						ImGui::TreePop();
					}

					// texture
					unsigned int ID2s = 0;
					for (auto it3 : it2->mTextures)
					{
						string name3 = wstringUnicodeToUTF8(it3->mName.c_str());
						ImGui::Text(u8"    <Texture>: %s", name3.c_str());

						ImGui::PushID(ID2s);
						if (ImGui::TreeNode(u8"テクスチャプロパティ"))
						{
							// テクスチャをImGuiで出す
							ImGui::Image((void*)it3->mTex, ImVec2(150, 150));

							// テクスチャパス
							static string path1 = wstringUnicodeToUTF8(it3->mPath);
							//ImGui::Text(u8"テクスチャパス:%s", path.data());
							this->mTexPathTemp = (char*)path1.c_str();
							ImGui::InputText(u8"テクスチャパス", this->mTexPathTemp, IM_ARRAYSIZE(this->mTexPathTemp));

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

		// 骨情報
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