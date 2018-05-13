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
	ImGui::CreateContext();
	// I/Oを初期化
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	// ImGuiを初期化
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	// スタイルカラーを決める
	ImGui::StyleColorsDark();
	// デフォルトフォント
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/UDDigiKyokashoN-R.ttc", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	// 各チェックを初期化
	this->mIsWireframe = false;
	this->mIsAddingModel = false;
}

//*****************************************************************************
//
// ImGuiとアプリケーションの操作分離
//
//*****************************************************************************
bool GUI::isAnyImGuiFocused()
{
	if (ImGui::IsAnyWindowFocused())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
//
// ImGuiの描画処理
//
//*****************************************************************************
void GUI::draw()
{
	// ImGuiバッファサイズを確定
	ImGui::GetIO().DisplaySize.x = SCREEN_WIDTH;
	ImGui::GetIO().DisplaySize.y = SCREEN_HEIGHT;

	//システム操作GUI
	systemGUI();

	// シーンGUI
	sceneGUI();

	// モデル読み込み
	if (this->mIsAddingModel == true)
	{
		addModelImGui();
	}

	// ドロップされたファイルが対象外
	if (this->mIsModelFile == false)
	{
		dropFileErrorGUI();
	}

	// ImGuiを描画
	if (this->mIsWireframe)
	{
		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
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
			ImGui::Separator();
		}

		// マウス位置
		{
			ImGui::TextUnformatted(u8"マウス位置:");
			ImGui::SameLine();
			ImGui::Text("%f,%f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			ImGui::Separator();
		}

		// レンダリングモード
		{
			// ワイヤフレームを塗りつぶす
			ImGui::TextUnformatted(u8"ワイヤフレームモード");
			ImGui::SameLine();
			if (ImGui::Button("WIREFRAME"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				this->mIsWireframe = true;
			}
			// 面を塗りつぶす
			ImGui::TextUnformatted(u8"ポリゴンモード      "); ImGui::SameLine();
			if (ImGui::Button("SOLID"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				this->mIsWireframe = false;
			}
			ImGui::Separator();
		}

		// スクリーンショット
		{
			ImGui::TextUnformatted(u8"スクリーンショット  "); ImGui::SameLine();
			if (ImGui::Button("SCREENSHOT"))
			{
				// バッファ画面を取得
				LPDIRECT3DSURFACE9 backBuffer;
				getD3DDevice()->GetRenderTarget(0, &backBuffer);

				// バッファサーフェイスを保存
				D3DXSaveSurfaceToFile(L"screenShot.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);

				// Debugウインドへ
				cout << "<System> ..\screenShot.bmp ... successed!" << endl;

				// バッファをリリース
				backBuffer->Release();
			}
			ImGui::Separator();
		}

		// システムカメラ
		{
			// シーンのカメラを取得
			Camera* camera = getSceneManager()->mCurrentScene->mCurrentCamera;

			if(ImGui::TreeNode(u8"システムカメラ"))
			{
				ImGui::TextUnformatted(u8"カメラ位置");
				float* v1[3] = { &camera->mCameraPos.x, &camera->mCameraPos.y, &camera->mCameraPos.z };
				ImGui::InputFloat3("Pos", *v1);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"カメラ注視点(モデル位置に設定してる)");
				float* v2[3] = { &camera->mTargetTrans->mPos.x, &camera->mTargetTrans->mPos.y, &camera->mTargetTrans->mPos.z };
				ImGui::InputFloat3("Look", *v2);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"注視方向ベクトル");
				float* v3[3] = { &camera->mCameraFront.x, &camera->mCameraFront.y, &camera->mCameraFront.z };
				ImGui::DragFloat3("lookV", *v3);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"右方向ベクトル");
				float* v4[3] = { &camera->mCameraRight.x, &camera->mCameraRight.y, &camera->mCameraRight.z };
				ImGui::DragFloat3("rightV", *v4);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"上方向ベクトル");
				float* v5[3] = { &camera->mCameraUp.x, &camera->mCameraUp.y, &camera->mCameraUp.z };
				ImGui::DragFloat3("upV", *v5);
				ImGui::Separator();

				ImGui::TreePop();
			}
			ImGui::Separator();
		}

		// レンダリングモードを選択
		{
			// 今ののレンダリングモード(デフォルトはテクスチャ)
			static int currentShadingMode = 2;

			// コンボボックスの幅を設定
			ImGui::PushItemWidth(160);
			ImGui::TextUnformatted(u8"レンダリングモード");
			ImGui::Combo("RenderMode", &currentShadingMode, this->mShadingMode, IM_ARRAYSIZE(this->mShadingMode));
			switch (currentShadingMode)
			{
			case 0:
				getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_DIFFUSE;
				break;
			case 1:
				getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_NORMAL;
				break;
			case 2:
				getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_TEXTURE;
				break;
			case 3:
				getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_SHADING;
				break;
			}
			ImGui::Separator();
		}

		// カラーラップ選択
		{
			// 今ののレンダリングモード(デフォルトはテクスチャ)
			static int currentColorRamp = 0;

			// コンボボックスの幅を設定
			ImGui::PushItemWidth(160);
			ImGui::TextUnformatted(u8"カラーランプモード");
			ImGui::Combo("ColorRamp", &currentColorRamp, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
			switch (currentColorRamp)
			{
			case 0:
				getSceneManager()->mCurrentScene->mShader->mColorRamp = CR_LINEAR;
				break;
			case 1:
				ImGui::TextUnformatted(u8"カラーセグメント");
				ImGui::SliderFloat("Level1", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.x, 0.0f, 1.0f);
				ImGui::SliderFloat("Level2", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.y, 0.0f, 1.0f);
				ImGui::SliderFloat("Level3", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.z, 0.0f, 1.0f);
				getSceneManager()->mCurrentScene->mShader->mColorRamp = CR_CONSTANT;
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
	// シーンのマルチレベルメニュー
	ImGui::Begin(u8"Scene"/*, nullptr, ImGuiWindowFlags_NoResize*/);
	{
		// GameObjectの作りメニュ―
		createNewGameObjectGUI();

		// 各GameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);

			// Todo
			// ライトと床、utf-8に変換しても出せない

			// wstring -> string
			string name1 = wstringUnicodeToUTF8(it.first);
			if (ImGui::TreeNode(u8"%s", name1.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// GameObjectの各コンポーネントを出す
				unsigned int ID2s = 0;
				for (auto it2 : it.second->mComponentsMap)
				{
					ImGui::PushID(ID2s);
					string name2 = it2.first.name();
					name2 = name2.substr(name2.find_last_of(" ") + 1, name2.size());		// exp: class xxx -> xxx
					if (ImGui::TreeNode(u8"%s", name2.c_str()))
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

	// サブウインド設定
	if (ImGui::BeginPopupModal("Create GameObject"))
	{

		ImGui::TextUnformatted(u8"GameObject名前");
		ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));

		if (ImGui::Button(u8"作り"))
		{
			// 新しいGameObjectを作る
			GameObject* gameObject = new GameObject();
			// string -> wstring
			wstring newGameObjectName = stringToWString(this->mNewGameObjectName);
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// mNewGameObjectName初期化
			*this->mNewGameObjectName = { NULL };

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

//*****************************************************************************
//
// モデル追加GUI
//
//*****************************************************************************
void GUI::addModelImGui()
{
	ImGui::Begin(u8"インポート");
	ImGui::TextUnformatted(u8"GameObject名前");
	ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));
	ImGui::TextUnformatted(u8"モデルファイルパス");
	string path = wStringToString(this->mAddingFilePath);
	ImGui::Text(u8"%s", path.c_str());

	// string -> wstring
	wstring newGameObjectName = stringToWString(this->mNewGameObjectName);

	// エラータイプ 0 -- default、1 -- Error1、2 -- Error2
	static int errorType = 0;

	// チェックGameObject名前
	if (ImGui::Button(u8"インポート"))
	{
		if (strlen(this->mNewGameObjectName) == 0 )
		{
			errorType = 1;
		}

		// チェックGameObject名前
		if (!isGameObjectNameRight(newGameObjectName))
		{
			errorType = 2;
		}

		if (errorType != 0)
		{
			// エラーウインドを開く
			ImGui::OpenPopup("Error");
		}
		else
		{
			// 新しいGameObjectを作る
			GameObject* gameObject = new GameObject();
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// モデルを読み込み
			//getResources()->createModel(this->mAddingFilePath);

			// mNewGameObjectName初期化
			*this->mNewGameObjectName = { NULL };
			
			this->mIsAddingModel = false;
		}
	}

	// エラーウインド
	if (ImGui::BeginPopupModal("Error"))
	{
		if (errorType == 1)
		{
			ImGui::TextUnformatted(u8"GameObject名前を入力してください");
		}
		if (errorType == 2)
		{
			ImGui::TextUnformatted(u8"このGameObject名前も存在してる");
		}

		if (ImGui::Button(u8"はい"))
		{
			// サブウインドを閉める
			ImGui::CloseCurrentPopup();

			// エラータイプ初期化
			errorType = 0;
		}

		ImGui::EndPopup();
	}

	// キャンセル
	ImGui::SameLine();
	if (ImGui::Button(u8"キャンセル"))
	{
		// mNewGameObjectName初期化
		*this->mNewGameObjectName = { NULL };

		this->mIsAddingModel = false;
	}

	if (this->mIsAddingModel == false)
	{
		// モデル追加GUIを閉める
		ImGui::CloseCurrentPopup();
	}

	ImGui::End();
}

//*****************************************************************************
//
// チェック追加GameObject名前
//
//*****************************************************************************
bool GUI::isGameObjectNameRight(wstring name)
{
	for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
	{
		// シーンに既にこの名前のGameObjectが存在すれば
		if (it.first == name)
		{
			return false;
		}
	}

	return true;
}

//*****************************************************************************
//
// ドロップファイルは対応できないGUI
//
//*****************************************************************************
void GUI::dropFileErrorGUI()
{
	ImGui::Begin(u8"Error");
	ImGui::TextUnformatted(u8"ドロップされたファイルはモデルファイルではありません！");
	if (ImGui::Button(u8"はい"))
	{
		this->mIsModelFile = false;
	}
	ImGui::End();
}