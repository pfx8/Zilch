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
#include "Engine/GUI.h"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
LPDIRECT3D9						gD3D {nullptr};				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9				gD3DDevice {nullptr};		// Deviceオブジェクト(描画に必要)
D3DPRESENT_PARAMETERS			gD3Dpp;						// デバイスのプレゼンテーションパラメータ

// 自作クラス
Console*						gConsole {nullptr};			// コンソールウインド
Resources*						gResources {nullptr};		// リソース
SceneManager*					gSceneManager {nullptr};	// シンー管理
GameTimes*						gGameTimes {nullptr};		// ゲームタイム
GUI*							gGUI {nullptr};				// ImGui

// ゲーム世界の3軸
WorldVector						gWorldVector;

// 読み込みできるファイル拡張子集合
// 詳しいは https://github.com/assimp/assimp
vector<string> modelFileExtension = { "x","fbx","obj","3ds" };

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
// ウィンド
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);					// ウインド
HRESULT initDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// DirectX初期化
HRESULT	initGame(HINSTANCE hInstance, HWND hWnd);						// ゲーム処理を初期化
void	updata(HWND hWnd, int cmd);										// ウインド更新処理
void	draw(HWND hWnd);												// ウインド描画処理
void	release(void);													// ウインド終了処理

// ドロップ処理
void onDropFiles(HWND hwnd, HDROP hDropInfo);							// ドロップファイル処理
void enumerateFiles();													// ファイルの列挙処理
void isModelFile(string path);											// モデルファイルかどうかを判断

// ImGui用プロシージャ
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	hWnd = CreateWindowEx
		(WS_EX_ACCEPTFILES,															// ドロップファイルを受け入れることを指定
		CLASS_NAME,
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
	timeBeginPeriod(1);									// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();		// ミリ秒単位で取得
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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
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
			// 1ミリ秒単位
			dwCurrentTime = timeGetTime();

			// 0.5秒ごとに実行
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// FPSを計測(ImGuiに任せった)
				//FPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);

				// FPS計測時刻を保存
				dwFPSLastTime = dwCurrentTime;
				// カウントをクリア
				dwFrameCount = 0;
			}

			// 1/60秒ごとに実行
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60.0f))
			{
				// 処理した時刻を保存
				dwExecLastTime = dwCurrentTime;

				// ImGui用フレームを作り
				ImGui_ImplDX9_NewFrame();
				// 更新処理
				updata(hWnd, nCmdShow);
				// 描画処理
				draw(hWnd);

				// 処理回数のカウントを加算
				dwFrameCount++;
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

	switch(message)
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

	case WM_DROPFILES:
		onDropFiles(hWnd, (HDROP)wParam);	// ドロップファイル処理
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
		cout << "[Error] DirectX initialization ... fail!" << endl;
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(gD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		cout << "[Error] Get displayer mode ... fail!" << endl;
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	// ワークをゼロクリア
	ZeroMemory(&gD3Dpp, sizeof(gD3Dpp));

	// デフォルトで使わない
	D3DMULTISAMPLE_TYPE multiSampType {D3DMULTISAMPLE_NONE};
	// このデバイスでマルチサンプリング テクニックを利用できるかどうかを調べる
	if (gD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8B8G8R8,
		0, D3DMULTISAMPLE_16_SAMPLES, NULL))
	{
		multiSampType = D3DMULTISAMPLE_16_SAMPLES; // 16倍
	}

	gD3Dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	gD3Dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	gD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	gD3Dpp.BackBufferCount = 1;							// バックバッファの数
	gD3Dpp.MultiSampleType = multiSampType;				// デバイスが適用できるフルシーン マルチサンプリングのレベルを定義
	gD3Dpp.MultiSampleQuality = 0;						// 品質レベルを設定
	gD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	gD3Dpp.hDeviceWindow = hWnd;						// ウインドHWND
	gD3Dpp.Windowed = bWindow;							// ウィンドウモード
	gD3Dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	gD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;			// デプスバッファとして16bitを使う
	gD3Dpp.Flags = 0;

	if (bWindow)
	{
		// ウィンドウモード
		gD3Dpp.FullScreen_RefreshRateInHz = 0;							// リフレッシュレート
		gD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{
		// フルスクリーンモード
		gD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
		gD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	D3DCAPS9 caps; 
	int vp {0};
	if (FAILED(gD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		cout << "[Error] Get directX device ... fail!" << endl;
		return E_FAIL;
	}

	// 頂点処理モードを選択
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// ハードウェアで頂点を処理する
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// ソフトウェアで頂点を処理する
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

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
		cout << "[Error] DirectX device initialization ... fail!" << endl;
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
	if (gConsole->mIsConsoleRun == false)
	{
		cout << "[Error] Setup console ... fail!" << endl;
		return E_FAIL;
	}

	// ゲーム時間初期化
	gGameTimes = new GameTimes();

	// シンーマネジメント初期化
	gSceneManager = new SceneManager();
	gSceneManager->start();

	// リソース初期化
	gResources = new Resources();

	// GUIを初期化
	gGUI = new GUI();
	gGUI->start(hWnd, gD3DDevice);

	return S_OK;
}

//*****************************************************************************
//
// ドロップファイル処理
//
//*****************************************************************************
void onDropFiles(HWND hwnd, HDROP hDropInfo)
{
	// ドロップされたファイル数を取得
	unsigned int fileCount {DragQueryFile(hDropInfo, (UINT)-1, NULL, 0)};
	// ドロップされたファイルパス
	TCHAR filePath[_MAX_PATH] {_T("")};
	// ドロップされたファイル情報
	DWORD attribute;

	// ドロップされたファイルとフォルダを取得
	for (unsigned int i = 0; i < fileCount; i++)
	{
		// ドロップされたファイル名を取得
		DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));
		// ドロップされたファイルの情報を取得
		attribute = GetFileAttributes(filePath);

		// フォルダならば
		if (attribute & FILE_ATTRIBUTE_DIRECTORY)
		{
			// 新しいディレクトリを設定
			SetCurrentDirectory(filePath);
			// 新しいディレクトリによってファイルを列挙処理
			enumerateFiles();
		}
		// ファイルならば
		else
		{
			break;
		}
	}

	// チェックファイル内容
	isModelFile(filePath);

	// ドロップ終了
	DragFinish(hDropInfo);
}

//*****************************************************************************
//
// ファイルの列挙処理
//
//*****************************************************************************
void enumerateFiles()
{
	// WIN32ファイルデータ
	WIN32_FIND_DATA findFileData;
	// 設定されたディレクトリにより検索ハンドルを指定
	// findFileDataにファイルの情報を入れる
	HANDLE find = FindFirstFile(_T("*.*"), &findFileData);

	if (find != INVALID_HANDLE_VALUE)
	{
		do
		{
			// ディレクトリかどうかをチェック
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//  親ディレクトリを無視
				if (_tcscmp(findFileData.cFileName, _T(".")) && _tcscmp(findFileData.cFileName, _T("..")))
				{
					// 新しいディレクトリを設定
					SetCurrentDirectory(findFileData.cFileName);
					enumerateFiles();
					SetCurrentDirectory(_T(".."));
				}
			}
			// ファイルならば
			else
			{
				string filePath;
				TCHAR directory[MAX_PATH];

				// 現在のディレクトリを取得
				GetCurrentDirectory(MAX_PATH, directory);
				filePath = directory;
				// ドロップされたオブジェクトのパスを取得
				filePath += findFileData.cFileName;
			}
		} while (FindNextFile(find, &findFileData));		// ディレクトリの下またファイルがあれば
	}

	FindClose(find);
}

//*****************************************************************************
//
// モデルファイルかどうかを判断
//
//*****************************************************************************
void isModelFile(string path)
{
	string fileFormat = path.substr(path.find_last_of(".") + 1, path.size());

	cout << "<test> " << path << endl;
	cout << "<test> " << fileFormat << endl;

	for (auto it : modelFileExtension)
	{
		if (it == fileFormat)
		{
			gGUI->mIsAddingModel = true;
			gGUI->mAddingFilePath = path;
			break;
		}
	}

	// 対象外
	gGUI->mIsDropFileError = true;
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void updata(HWND hWnd, int cmd)
{
	// ImGuiを操作してない時だけアプリケーションの操作を更新
	if (gGUI->isAnyImGuiFocused() == false)
	{
		// 入力更新
		UpdateInput();
	}

	// ゲームタイムを更新
	gGameTimes->update();

	// シンーを更新する
	gSceneManager->update();
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void draw(HWND hWnd)
{
	// Direct3Dによる描画の開始
	if (SUCCEEDED(gD3DDevice->BeginScene()))
	{
		// シーンを描画
		gSceneManager->draw();

		// GUIを描画
		gGUI->draw();

		gD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	gD3DDevice->Present(NULL, NULL, NULL, NULL);
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
	RELEASE_CLASS_POINT(gGUI);

	// リリースLPDIRECT3D9
	RELEASE_POINT(gD3D);
	
	// 入力処理の終了処理
	UninitInput();
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