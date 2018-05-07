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
		D3DXVECTOR3 pos = this->mGameObject->mScene->getGameObject("pointLight")->getComponent<PointLight>()->mLightPos;
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
	// ライトを設定
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

	// モデルのワールド変換行列を取得
	Transform* trans = this->mGameObject->getComponent<Transform>();
	// モデルのワールド変換行列と回転行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);
	this->mShader->mEffect->SetMatrix("rotMatrix", &trans->mRotMatrix);

	// カメラ情報を取得
	Camera* camera = this->mGameObject->mScene->getGameObject("mainCamera")->getComponent<Camera>();
	// カメラの行列をシェーダーに渡る
	this->mShader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	this->mShader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	// レンダリングモードをシェーダーに渡す
	this->mShader->mEffect->SetInt("renderType", this->mShader->mRenderType);

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
		// メッシュ情報
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

		// 骨情報
		if (this->mModel->mMeshType == MT_withBone)
		{
			if (ImGui::TreeNode(u8"ボーン"))
			{
				unsigned int level = 0;
				this->mModel->traverseNode(*(this->mModel->mAnimationes.at(0)->mNode.end() - 1), level);

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}