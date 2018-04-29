//*****************************************************************************
//
// ゲーム処理[main.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine/Engine.h"
#include "Engine/Console.h"
#include "Engine/SceneManager.h"
#include "Engine/input.h"
#include "Engine/GameTimes.h"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
LPDIRECT3D9						gD3D = nullptr;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9				gD3DDevice = nullptr;		// Deviceオブジェクト(描画に必要)
D3DPRESENT_PARAMETERS			gD3Dpp;						// デバイスのプレゼンテーションパラメータ

// 自作クラス
Console*						gConsole;					// コンソールウインド
Resources*						gResources;					// リソース
SceneManager*					gSceneManager;				// シンー管理
GameTimes*						gGameTimes;					// ゲームタイム

// ゲーム世界の3軸
WorldVector						gWorldVector;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);					// ウインド
HRESULT initDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// DirectX初期化
HRESULT	initGame(HINSTANCE hInstance, HWND hWnd);						// ゲーム処理を初期化
void	updata(HWND hWnd, int cmd);										// ウインド更新処理
void	draw(HWND hWnd);												// ウインド描画処理
void	release(void);													// ウインド終了処理
void	drawImGui(void);												// ImGui描画

//*****************************************************************************
//
// ウインドのメイン関数
//
//*****************************************************************************
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));

	// ウィンドウを初期化
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用(*35)
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//*****************************************************************************
	//
	// ウィンドウの設定
	//
	//*****************************************************************************
	
	// ウィンドウ属性を設定
	WNDCLASSEX	wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = NULL;

	// ウインド用変数
	HWND hWnd;	// ウインドのID
	MSG	 msg;	// ウインドメッセージ

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// システム解像度を取得
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	// どんな解像度でもウインドを中心にする
	int x = (rect.right - rect.left - SCREEN_WIDTH) / 2;
	int y = (rect.bottom - rect.top - SCREEN_HEIGHT) / 2;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		x,																			// ウィンドウの左座標
		y,																			// ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,										// ウィンドウ横幅 + 左右ウインドの太さ
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅 + 上下ウインドの太さ
		NULL,
		NULL,
		hInstance,
		NULL);

	//*****************************************************************************
	//
	// 各初期化
	//
	//*****************************************************************************
	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(initDiretX(hInstance, hWnd, true)))
	{
		return E_FAIL;
	}

	// フレームカウント初期
	timeBeginPeriod(1);									//分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();		//ミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ゲーム初期化
	if (FAILED(initGame(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ウインドウの表示(InitDiretX()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//イベントと先生が呼んだ。
		{
			if (msg.message == WM_QUIT)
			{
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			dwCurrentTime = timeGetTime();				// 1ミリ秒単位

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				// ImGuiに任せった
				//FPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);	// FPSを計測

				dwFPSLastTime = dwCurrentTime;			// FPS計測時刻を保存
				dwFrameCount = 0;						// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;			// 処理した時刻を保存

				// ImGui用フレームを作り
				ImGui_ImplDX9_NewFrame();
				// 更新処理
				updata(hWnd, nCmdShow);
				// 描画処理
				draw(hWnd);

				dwFrameCount++;							// 処理回数のカウントを加算
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ウインド終了処理
	release();

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//*****************************************************************************
//
// プロシージャ
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}

	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//*****************************************************************************
//
// DirectX初期化
//
//*****************************************************************************
HRESULT initDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	gD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (gD3D == nullptr)
	{
		cout << "[Error] DirectX initialization ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(gD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		cout << "[Error] Get displayer mode ... fail!" << endl;		// エラーメッセージ
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&gD3Dpp, sizeof(gD3Dpp));								// ワークをゼロクリア

	D3DMULTISAMPLE_TYPE multiSampType = D3DMULTISAMPLE_NONE;		// デフォルトで使わない
	if (gD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8B8G8R8,
		0, D3DMULTISAMPLE_16_SAMPLES, NULL))
	{
		multiSampType = D3DMULTISAMPLE_16_SAMPLES; // 16倍
	}

	gD3Dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	gD3Dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	gD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	gD3Dpp.BackBufferCount = 1;							// バックバッファの数
	gD3Dpp.MultiSampleType = multiSampType;				// 
	gD3Dpp.MultiSampleQuality = 0;						// 
	gD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	gD3Dpp.hDeviceWindow = hWnd;
	gD3Dpp.Windowed = bWindow;							// ウィンドウモード
	gD3Dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	gD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;		// デプスバッファとして16bitを使う
	gD3Dpp.Flags = 0;

	if (bWindow)
	{
		// ウィンドウモード
		// d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		gD3Dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		gD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{
		// フルスクリーンモード
		// d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		gD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
		gD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	D3DCAPS9 caps; 
	int vp = 0;
	if (FAILED(gD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		cout << "[Error] Get directX device ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// ハードウェアで頂点を処理する
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// ソフトウェアで頂点を処理する

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(gD3D->CreateDevice(D3DADAPTER_DEFAULT,		// ディスプレイアダプタ
		D3DDEVTYPE_HAL,										// ディスプレイタイプ
		hWnd,												// フォーカスするウインドウへのハンドル
		vp,													// デバイス作成制御の組み合わせ
		&gD3Dpp,											// デバイスのプレゼンテーションパラメータ
		&gD3DDevice)))										// デバイスインターフェースへのポインタ
	{
		cout << "[Error] DirectX device initialization ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//
// ゲーム処理を初期化
//
//*****************************************************************************
HRESULT initGame(HINSTANCE hInstance, HWND hWnd)
{
	// input初期化
	InitInput(hInstance, hWnd);

	// メッセージを出る為のコンソールを初期化
	gConsole = new Console();
	if (gConsole->isConsoleRun == false)
	{
		cout << "[Error] Set console ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	// ゲーム時間初期化
	gGameTimes = new GameTimes();

	// シンーマネジメント初期化
	gSceneManager = new SceneManager();
	gSceneManager->start();

	// リソース初期化
	gResources = new Resources();

	// ImGuiを初期化
	ImGui::CreateContext();
	// I/Oを取得
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplDX9_Init(hWnd, gD3DDevice);
	// スタイルカラーを決める
	ImGui::StyleColorsDark();
	// デフォルトフォント
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/UDDigiKyokashoN-R.ttc", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	return S_OK;
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void updata(HWND hWnd, int cmd)
{
	gGameTimes->update();			// ゲームタイムを更新
	UpdateInput();					// 入力更新
	gSceneManager->update();		// シンーを更新する
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void draw(HWND hWnd)
{
	// バックバッファ＆Ｚバッファのクリア
	//gD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(155, 255, 255, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(gD3DDevice->BeginScene()))
	{
		// シーンを描画
		gSceneManager->draw();

		// ImGuiを描画
		drawImGui();

		gD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	gD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// ImGui描画
//
//*****************************************************************************
void drawImGui(void)
{
	// デッバグウインド(メインウインド)
	{
		ImGui::Begin(u8"デバッグウインド"/*, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);

		// FPSとタイム
		{
			ImGui::Text("Fps:%.1f, Time:%.3fs", ImGui::GetIO().Framerate, gGameTimes->mCurrentTime);
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
				gD3DDevice->GetRenderTarget(0, &backBuffer);

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
				gSceneManager->mCurrentScene->mShader->mRenderType = RT_DIFFUSE;
				break;
			case 1:
				gSceneManager->mCurrentScene->mShader->mRenderType = RT_NORMAL;
				break;
			case 2:
				gSceneManager->mCurrentScene->mShader->mRenderType = RT_TEXTURE;
				break;
			case 3:
				gSceneManager->mCurrentScene->mShader->mRenderType = RT_SHADING;
				break;
			}
		}
		ImGui::End();
	}

	// ImGuiを描画
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//*****************************************************************************
//
// 終了処理
//
//*****************************************************************************
void release(void)
{
	RELEASE_POINT(gD3D);
	RELEASE_POINT(gD3DDevice);
	RELEASE_CLASS_POINT(gConsole);
	RELEASE_CLASS_POINT(gSceneManager);
	RELEASE_CLASS_POINT(gResources);
	RELEASE_CLASS_POINT(gGameTimes);

	// リリースLPDIRECT3D9
	RELEASE_POINT(gD3D);
	
	// 入力処理の終了処理
	UninitInput();

	// ImGui終了処理
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
}

//*****************************************************************************
//
// デバイス取得関数
//
// 他のファイルの中に、グローバル変数を渡すとき、こういうGET関数が必要だ。
//
//*****************************************************************************
LPDIRECT3DDEVICE9 getD3DDevice(void)
{
	return gD3DDevice;
}

//*****************************************************************************
//
// リソースを取得
//
//*****************************************************************************
Resources* getResources(void)
{
	return gResources;
}

//*****************************************************************************
//
// ゲームタイムを取得
//
//*****************************************************************************
GameTimes* getGameTimes(void)
{
	return gGameTimes;
}

//*****************************************************************************
//
// シーン管理ポインタを取得
//
//*****************************************************************************
SceneManager* getSceneManager(void)
{
	return gSceneManager;
}