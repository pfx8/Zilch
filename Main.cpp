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
#include "Engine\DebugMessage.h"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
int										gFPS;										// FPSカウンタ
LPDIRECT3D9						gD3D = nullptr;						// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		gD3DDevice = nullptr;			// Deviceオブジェクト(描画に必要)

Console*								gConsole;								// コンソールウインド
Resources*							gResources;							// リソース
SceneManager*					gSceneManager;					// シンー管理
GameTimes*						gGameTimes;							// ゲームタイム
DebugMessage*				gDebugMessage;					// デバッグメッセージ

WorldVector						gWorldVector;						// ゲーム世界の3軸

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void	Updata(HWND hWnd, int cmd);
void	draw(HWND hWnd);
void	Release(void);

//*****************************************************************************
//
// メイン関数
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

	// フレームカウント初期化(*35)
	timeBeginPeriod(1);		//分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();		//ミリ秒単位で取得 syutoku
	dwCurrentTime = dwFrameCount = 0;

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

	HWND		hWnd;		// ハンドル
	MSG			msg;		// メッセージ

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wcex))
		return -1;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_WIDTH,																		// ウィンドウ横幅
		SCREEN_HEIGHT,																		// ウィンドウ縦幅
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
	if (FAILED(InitDiretX(hInstance, hWnd, true)))
	{
		return E_FAIL;
	}

	// メッセージを出る為のコンソールを初期化
	gConsole = new Console();
	if (gConsole->isConsoleRun == false)
	{
		cout << "[Error] Set console ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	// ゲーム時間
	gGameTimes = new GameTimes();

	// シンーマネジメント
	gSceneManager = new SceneManager();
	gSceneManager->start();

	// リソース
	gResources = new Resources();

	// デバッグメッセージ
	gDebugMessage = new DebugMessage();

	//ヴインドウを中心に移動
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	MoveWindow(hWnd,
		(rect.right - rect.left - SCREEN_WIDTH) / 2,
		(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		true);

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
			dwCurrentTime = timeGetTime();	//1ミリ秒単位

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	//0.5秒ごとに実行
			{
				gFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	//FPSを計測

				dwFPSLastTime = dwCurrentTime;	//FPS計測時刻を保存

				dwFrameCount = 0;	//カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	//1/60秒ごとに実行
			{
				char str[256] = {};
				sprintf(str, _T("Project : Zilch ... %d"), gFPS);
				SetWindowText(hWnd, str);

				dwExecLastTime = dwCurrentTime;	//処理した時刻を保存
				Updata(hWnd, nCmdShow);					// 更新処理
				draw(hWnd);											// 描画処理
				dwFrameCount++;								//処理回数のカウントを加算
				if (dwFrameCount == 60)						// 60フレームを確定
					continue;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Release();

	return (int)msg.wParam;
}

//*****************************************************************************
//
// プロシージャ
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		draw(hWnd);
		ValidateRect(hWnd, NULL);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:			// [ESC]キーが押された
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
// 初期化処理
//
//*****************************************************************************
HRESULT InitDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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
		cout << "[Error] Get displayer mode ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア


	D3DMULTISAMPLE_TYPE multiSampType = D3DMULTISAMPLE_NONE; // デフォルトで使わない
	if (gD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8B8G8R8,
		0, D3DMULTISAMPLE_4_SAMPLES, NULL))
	{
		multiSampType = D3DMULTISAMPLE_8_SAMPLES; // 4倍
	}

	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.MultiSampleType = multiSampType;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWindow;							// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		// デプスバッファとして16bitを使う
	d3dpp.Flags = 0;

	if (bWindow)
	{
		// ウィンドウモード
		// d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{
		// フルスクリーンモード
		// d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
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
	if (FAILED(gD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		vp,											// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&gD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		cout << "[Error] DirectX device initialization ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	gD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);												// Zバッファを使用
	gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);						// αブレンドを行う
	gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	RELEASE_POINT(gD3D); // リリースLPDIRECT3D9

	//*****************************************************************************
	//
	// input
	//
	//*****************************************************************************
	InitInput(hInstance, hWnd);

	return S_OK;
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void Updata(HWND hWnd, int cmd)
{
	// システム変更
	// 塗りつぶしモード
	if (GetKeyboardTrigger(DIK_F1))			// key F1
	{
		// ワイヤフレームを塗りつぶす
		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		cout << "[Information] <RenderState> : [WIREFRAME]" << endl;	// コンソールにメッセージを出す
	}

	if (GetKeyboardTrigger(DIK_F2))			// key F2
	{
		// 面を塗りつぶす
		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		cout << "[Information] <RenderState> : [SOLID]" << endl;	// コンソールにメッセージを出す
	}

	gGameTimes->update();			// ゲームタイムを更新
	UpdateInput();							// 入力更新
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
	gD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(getD3DDevice()->BeginScene()))
	{
		// シーンを描画
		gSceneManager->draw();

		// デバッグメッセージを描画
		gDebugMessage->draw();

		getD3DDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	getD3DDevice()->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// 終了処理
//
//*****************************************************************************
void Release(void)
{
	RELEASE_POINT(gD3D);
	RELEASE_POINT(gD3DDevice);
	RELEASE_CLASS_POINT(gConsole);
	RELEASE_CLASS_POINT(gSceneManager);
	RELEASE_CLASS_POINT(gResources);
	RELEASE_CLASS_POINT(gGameTimes);
	RELEASE_CLASS_POINT(gDebugMessage);
	
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
// デバッグメッセージを取得
//
//*****************************************************************************
DebugMessage* getDebugMessage(void)
{
	return gDebugMessage;
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