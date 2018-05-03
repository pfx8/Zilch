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

		// シェーディング変更
		{
			const char* shaderName[] = { u8"ディフューズ", u8"ノーマル", u8"テクスチャ色", u8"シェーディング" };
			// chooseの選択を保存するためにstaticを使った
			static int choose = 1;
			ImGui::Combo(u8"シェーディングモード", &choose, shaderName, IM_ARRAYSIZE(shaderName));
			switch (choose)
			{
			case 0:
				getSceneManager()->mCurrentScene->mShader->mRenderType = RT_DIFFUSE;
				break;
			case 1:
				getSceneManager()->mCurrentScene->mShader->mRenderType = RT_NORMAL;
				break;
			case 2:
				getSceneManager()->mCurrentScene->mShader->mRenderType = RT_TEXTURE;
				break;
			case 3:
				getSceneManager()->mCurrentScene->mShader->mRenderType = RT_SHADING;
				break;
			}
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

}