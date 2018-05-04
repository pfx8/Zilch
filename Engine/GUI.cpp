//*****************************************************************************
//
// GUI処理[GUI.cpp]
//
// Author : LIAO HANCHEN
//
//****************************************************************************
#include "GUI.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
GUI::GUI()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
GUI::~GUI()
{
	// ImGui終了処理
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
}

//*****************************************************************************
//
// ImGui初期化
//
//*****************************************************************************
void GUI::start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice)
{
	// ImGuiを初期化
	ImGui::CreateContext();
	// I/Oを取得
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	// スタイルカラーを決める
	ImGui::StyleColorsDark();
	// デフォルトフォント
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/UDDigiKyokashoN-R.ttc", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
}

//*****************************************************************************
//
// ImGuiの描画処理
//
//*****************************************************************************
void GUI::draw()
{
	//システム操作GUI
	systemGUI();

	// シーンGUI
	sceneGUI();

	// ImGuiを描画
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//*****************************************************************************
//
// システム操作GUI
//
//*****************************************************************************
void GUI::systemGUI()
{
	// デッバグウインド(メインウインド)
	{
		ImGui::Begin(u8"デバッグウインド"/*, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);

		// FPSとタイム
		{
			ImGui::Text("Fps:%.1f, Time:%.3fs", ImGui::GetIO().Framerate, getGameTimes()->mCurrentTime);
			// FPSをプロット図で出す
			const float my_values[] = { ImGui::GetIO().Framerate, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
			ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));
			ImGui::Separator();
		}

		// マウス位置
		{
			ImGui::Text(u8"マウス位置:"); ImGui::SameLine();
			ImGui::Text("%f,%f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			ImGui::Separator();
		}

		// レンダリングモード
		{
			// ワイヤフレームを塗りつぶす
			ImGui::Text(u8"ワイヤフレームモード"); ImGui::SameLine();
			if (ImGui::Button("WIREFRAME"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			// 面を塗りつぶす
			ImGui::Text(u8"ポリゴンモード      "); ImGui::SameLine();
			if (ImGui::Button("SOLID"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
			ImGui::Separator();
		}

		// スクリーンショット
		{
			ImGui::Text(u8"スクリーンショット  "); ImGui::SameLine();
			if (ImGui::Button("SCREENSHOT"))
			{
				// バッファ画面を取得
				LPDIRECT3DSURFACE9 backBuffer;
				getD3DDevice()->GetRenderTarget(0, &backBuffer);

				// バッファサーフェイスを保存
				D3DXSaveSurfaceToFile("screenShot.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);

				// バッファをリリース
				backBuffer->Release();
			}
			ImGui::Separator();
		}
		ImGui::End();
	}
}

//*****************************************************************************
//
// シーンGUI
//
//*****************************************************************************
void GUI::sceneGUI()
{
	// シーンのマルチレベルメニュー
	ImGui::Begin(u8"Scene");
	{
		// GameObjectの作りメニュ―
		createNewGameObjectGUI();

		// 各GameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);
			if (ImGui::TreeNode(u8"%s", it.first.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// GameObjectの各コンポーネントを出す
				unsigned int ID2s = 0;
				for (auto it2 : it.second->mComponentsMap)
				{
					ImGui::PushID(ID2s);
					string name = it2.first.name();
					name = name.substr(name.find_last_of(" ") + 1, name.size());		// exp: class xxx -> xxx
					if (ImGui::TreeNode(u8"%s", name.c_str()))
					{
						it2.second->drawImGui();
						ImGui::TreePop();
					}

					ID2s++;
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			IDs++;
			ImGui::PopID();
		}
		
	}
	ImGui::End();
}

//*****************************************************************************
//
//  新しいGameObjectを作りメニュー
//
//*****************************************************************************
void GUI::createNewGameObjectGUI()
{
	if (ImGui::Button("Create GameObject"))
	{
		// サブウインドを開く
		ImGui::OpenPopup("Create GameObject");
	}

	// サブウインド
	if (ImGui::BeginPopupModal("Create GameObject"))
	{

		ImGui::Text(u8"GameObject名前");
		ImGui::InputText(" ", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));

		if (ImGui::Button(u8"作る"))
		{
			// 新しいGameObjectを作る
			GameObject* gameObject = new GameObject();
			getSceneManager()->mCurrentScene->addGameObject(this->mNewGameObjectName, gameObject);

			// サブウインドを閉める
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"キャンセル"))
		{
			// サブウインドを閉める
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}