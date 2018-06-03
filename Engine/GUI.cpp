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
GUI::GUI(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
GUI::~GUI(void)
{
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
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	ImGui::StyleColorsDark();

	// I/Oを初期化
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImFont* font = io.Fonts->AddFontFromFileTTF("Resources\\Font\\NotoSansCJKjp-Regular.otf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	io.FontDefault = font;

	// 各チェックを初期化
	this->mIsWireframe = false;
	this->mIsAddingModel = false;
	this->mIsModelFile = true;
	this->mCurrentRenderingMode = RM_TEXTURE;	// デフォルトはテクスチャモード
	this->mCurrentColorRampType = CR_LINEAR;	// デフォルトはリニアモード
	this->mCurrentLanguage = 0;					// デフォルトは日本語
}

//*****************************************************************************
//
// ImGuiとアプリケーションの操作分離
//
//*****************************************************************************
bool GUI::isAnyImGuiFocused(void)
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
void GUI::draw(void)
{
	// ImGuiバッファサイズを確定
	ImGui::GetIO().DisplaySize.x = SCREEN_WIDTH;
	ImGui::GetIO().DisplaySize.y = SCREEN_HEIGHT;

	//システム操作GUI
	systemGUI();

	// シーンGUI
	sceneGUI();

	// モデル追加ウインドウをチェック
	if (this->mIsAddingModel == true)
	{
		addModelImGui();
	}

	// ドロップファイルエラーウインドウをチェック
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
void GUI::systemGUI(void)
{
	ImGui::Begin(u8"デバッグウインド", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	// 言語選択 -- 実装できない
	{
		ImGui::Combo(u8"言語", &this->mCurrentLanguage, this->mLanguage, IM_ARRAYSIZE(this->mLanguage));
		ImGui::Separator();
	}

	// FPSとタイム
	{
		ImGui::Text("Fps:%.3f fps, Time:%.3f s/fps", ImGui::GetIO().Framerate, getGameTimes()->mDeltaTime);
		ImGui::Separator();
	}

	// マウス位置
	{
		ImGui::Text("%f, %f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::SameLine();
		ImGui::Text(u8"マウス位置");
		ImGui::Separator();
	}

	// レンダリングモード
	{
		// ワイヤフレームを塗りつぶす
		ImGui::TextUnformatted(u8"塗りつぶす");
		if (ImGui::Button(u8"ワイヤーフレーム"))
		{
			getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			this->mIsWireframe = true;
		}
		// 面を塗りつぶす
		ImGui::SameLine();
		if (ImGui::Button(u8"ポリゴンモード"))
		{
			getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			this->mIsWireframe = false;
		}
		ImGui::Separator();
	}

	// スクリーンショット
	{
		ImGui::TextUnformatted(u8"機能");
		if (ImGui::Button(u8"スクリーンショット"))
		{
			ImGui::OpenPopup(u8"スクリーンショット");
		}
		ImGui::Separator();

		if (ImGui::BeginPopupModal(u8"スクリーンショット"))
		{
			// バッファ画面を取得
			static LPDIRECT3DSURFACE9 backBuffer = nullptr;
			getD3DDevice()->GetRenderTarget(0, &backBuffer);

			ImGui::TextUnformatted(u8"スクリーンショット.bmpが保存されました！");
			if (ImGui::Button(u8"はい"))
			{
				// バッファサーフェイスを保存
				D3DXSaveSurfaceToFile(L"スクリーンショット.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);
				wcout << L"<System> ..\\スクリーンショット.bmp ... successed!" << endl;

				// バッファをnullptrする
				backBuffer = nullptr;

				// サブウインドを閉める
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	// システムカメラ
	{
		// シーンのカメラを取得
		Camera* camera = getSceneManager()->mCurrentScene->mCurrentCamera;

		if (ImGui::TreeNode(u8"システムカメラ"))
		{
			float* v1[3] = { &camera->mCameraPos.x, &camera->mCameraPos.y, &camera->mCameraPos.z };
			ImGui::TextUnformatted(u8"位置");
			ImGui::InputFloat3(u8"Pos", *v1);
			ImGui::Separator();

			float* v2[3] = { &camera->mTargetPos.x, &camera->mTargetPos.y, &camera->mTargetPos.z };
			ImGui::TextUnformatted(u8"注視点");
			ImGui::InputFloat3(u8"At", *v2);
			ImGui::Separator();

			float* v3[3] = { &camera->mCameraFront.x, &camera->mCameraFront.y, &camera->mCameraFront.z };
			ImGui::TextUnformatted(u8"注視方向");
			ImGui::DragFloat3(u8"Look", *v3);
			ImGui::Separator();

			float* v4[3] = { &camera->mCameraRight.x, &camera->mCameraRight.y, &camera->mCameraRight.z };
			ImGui::TextUnformatted(u8"右方向");
			ImGui::DragFloat3(u8"Right", *v4);
			ImGui::Separator();

			float* v5[3] = { &camera->mCameraUp.x, &camera->mCameraUp.y, &camera->mCameraUp.z };
			ImGui::TextUnformatted(u8"上方向");
			ImGui::DragFloat3(u8"Up", *v5);
			ImGui::Separator();

			ImGui::TreePop();
		}
		ImGui::Separator();
	}

	// レンダリングモードを選択
	{
		// コンボボックスの幅を設定
		ImGui::PushItemWidth(160);
		ImGui::TextUnformatted(u8"レンダリングモード");
		ImGui::Combo(u8"RenderingMode", (int*)&this->mCurrentRenderingMode, this->mRenderingMode, IM_ARRAYSIZE(this->mRenderingMode));
		switch (this->mCurrentRenderingMode)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_TEXTURE;
			break;
		case 1:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_DIFFUSE;
			break;
		case 2:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_SPECULAR;
			break;
		case 3:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_NORMAL;
			break;
		case 4:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_SHADING;
			break;
		}
		ImGui::Separator();
	}

	// カラーラップ選択
	{
		// コンボボックスの幅を設定
		ImGui::PushItemWidth(160);
		ImGui::TextUnformatted(u8"カラーランプモード");
		ImGui::Combo(u8"ColorRamp", (int*)&this->mCurrentColorRampType, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
		switch (this->mCurrentColorRampType)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mColorRampType = CR_LINEAR;
			break;
		case 1:
			D3DXVECTOR3* colorRampSegment = &getSceneManager()->mCurrentScene->mShader->mColorRampSegment;

			ImGui::TextUnformatted(u8"カラーセグメント");
			ImGui::SliderFloat("Level1", &colorRampSegment->x, 0.0f, 1.0f);
			if (colorRampSegment->x > colorRampSegment->y)
			{
				colorRampSegment->y = colorRampSegment->x;
			}

			ImGui::SliderFloat("Level2", &colorRampSegment->y, 0.0f, 1.0f);
			if (colorRampSegment->y > colorRampSegment->z)
			{
				colorRampSegment->z = colorRampSegment->y;
			}

			ImGui::SliderFloat("Level3", &colorRampSegment->z, 0.0f, 1.0f);
			if (colorRampSegment->z < colorRampSegment->y)
			{
				colorRampSegment->y = colorRampSegment->z;
			}
			if (colorRampSegment->y < colorRampSegment->x)
			{
				colorRampSegment->x = colorRampSegment->y;
			}

			getSceneManager()->mCurrentScene->mShader->mColorRampType = CR_CONSTANT;
			break;
		}
	}

	ImGui::End();
}

//*****************************************************************************
//
// シーンGUI
//
//*****************************************************************************
void GUI::sceneGUI(void)
{
	// シーンのマルチレベルメニュー
	ImGui::SetNextWindowSize(ImVec2(364,742));
	ImGui::Begin(u8"シーン", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	{
		// GameObjectの作りメニュ―
		//createNewGameObjectGUI();

		// BGカラー
		ImGui::ColorEdit4(u8"ライトカラー", getSceneManager()->mCurrentScene->mBGColor, ImGuiColorEditFlags_RGB);
		ImGui::Separator();

		// 各GameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);
			string name1 = wstringToString(it.first);
			if (ImGui::TreeNode("gameObject", u8"%s", name1.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
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
void GUI::createNewGameObjectGUI(void)
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
			wstring newGameObjectName = stringToWstring(this->mNewGameObjectName);
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
void GUI::addModelImGui(void)
{
	ImGui::Begin(u8"インポート");
	ImGui::TextUnformatted(u8"GameObject名前");
	ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));
	ImGui::TextUnformatted(u8"モデルファイルパス");
	string path = wstringToString(this->mAddingFilePath);
	ImGui::Text(u8"%s", path.c_str());

	wstring newGameObjectName = stringToWstring(this->mNewGameObjectName);

	// エラータイプ 0 -- default、1 -- Error1、2 -- Error2
	static int errorType = 0;

	// チェックGameObject名前
	if (ImGui::Button(u8"インポート"))
	{
		if (strlen(this->mNewGameObjectName) == 0 )
		{
			// GameObject名前がない
			errorType = 1;
		}

		if (!isGameObjectNameRight(newGameObjectName))
		{
			// GameObject名前が違法
			errorType = 2;
		}

		if (errorType != 0)
		{
			// エラーウインドを開く
			ImGui::OpenPopup("Error");
		}
		else
		{
			// モデルを読み込み
			getResources()->createModel(this->mAddingFilePath);

			// 新しいGameObjectを作る
			GameObject* gameObject = new GameObject();
			Transform* transform = new Transform();												// デフォルトはpos(0,0,0)、scl(1,1,1)、rot(0,0,0)
			gameObject->addComponent<Transform>(transform);
			MeshRender* meshRender = new MeshRender();
			wstring name = pathToFileName(this->mAddingFilePath);
			meshRender->mModel = getResources()->getModel(name);
			getSceneManager()->mCurrentScene->mMeshRenders.push_back(meshRender);
			gameObject->addComponent<MeshRender>(meshRender);
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// this->mNewGameObjectName初期化
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
void GUI::dropFileErrorGUI(void)
{
	ImGui::Begin(u8"Error");
	ImGui::TextUnformatted(u8"ドロップされたファイルはモデルファイルではありません！");
	if (ImGui::Button(u8"はい"))
	{
		// ウインドウを閉じる
		this->mIsModelFile = true;
	}
	ImGui::End();
}