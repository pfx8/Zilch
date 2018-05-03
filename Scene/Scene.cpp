//*****************************************************************************
//
// シーン処理 [Scene.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene::Scene()
{	

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{

}

//*****************************************************************************
//
// シーンにGameObjectを添付
//
//*****************************************************************************
void Scene::addGameObject(string name, GameObject* gameObject)
{
	gameObject->mScene = this;
	mGameObjectMap.insert({ name, gameObject });
}

//*****************************************************************************
//
// シーンからGameObjectを取得
//
//*****************************************************************************
GameObject* Scene::getGameObject(string name)
{
	if (mGameObjectMap.find(name) != mGameObjectMap.end())
	{
		return mGameObjectMap[name];
	}
	cout << "[Error] <GameObject> Get " << name << " failed!" << endl;
	return nullptr;
}

//*****************************************************************************
//
// シーンの更新
//
//*****************************************************************************
void Scene::update()
{
	// GUI更新
	updateImgui();

	// 各GameObjectを更新
	for (auto it : this->mGameObjectMap)
	{
		if (it.second->mActive == true)
		{
			it.second->update();
		}
	}
}

//*****************************************************************************
//
// GUI更新
//
//*****************************************************************************
void Scene::updateImgui()
{
	// シーンのマルチレベルメニュー
	ImGui::Begin(u8"Scene");
	{
		// GameObjectを作りメニュ―
		{
			static bool open = false;

			if (ImGui::Button("Create GameObject"))
			{
				// サブウインドを開く
				open = true;
				ImGui::OpenPopup("Settings");
			}

			if (open == true)
			{
				ImGui::BeginChild("Create GameObject");
				static char name[20];
				ImGui::Text(u8"GameObject名前");
				ImGui::InputText(" ", name, IM_ARRAYSIZE(name));

				if (ImGui::Button(u8"作る"))
				{
					// 新しいGameObjectを作る
					GameObject* gameObject = new GameObject();
					this->addGameObject(name, gameObject);

					// サブウインドを閉じる
					open = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"キャンセル"))
				{
					// サブウインドを閉じる
					open = false;
				}
				ImGui::EndChild();
			}
		}

		// 各GameObjectを出す
		{
			for (auto it : this->mGameObjectMap)
			{
				if (ImGui::TreeNode(u8"%s", it.first.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
				{
					//ImGui::Text("test");
					// ImGuiで各GameObjectの各コンポーネントを出す
					for (auto it2 : it.second->mComponentsMap)
					{
						if (ImGui::TreeNode(u8"%s", it2.first.c_str()))
						{
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
			}
		}
	}
	ImGui::End();
}

//*****************************************************************************
//
// シーンの描画
//
//*****************************************************************************
void Scene::draw()
{
	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(55, 155, 155, 255), 1.0f, 0);
	//シャドウマップ
	for (auto it : mMeshRenders)
	{
		if (it->mStart == true)
		{
			if (it->mIsDrawShadow == true)
			{
				it->drawShadowMap();
			}
		}
	}

	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(55, 155, 155, 255), 1.0f, 0);
	// メッシュ
	for (auto it : mMeshRenders)
	{
		if (it->mStart == true)
		{
			it->draw();
		}
	}
}