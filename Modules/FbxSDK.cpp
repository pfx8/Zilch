//*****************************************************************************
//
// FbxSDK処理 [FbxSDK.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "FbxSdk.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
FbxSDK::FbxSDK()
{
	manager = NULL;
	importer = NULL;
	scene = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
FbxSDK::~FbxSDK()
{
	// SDKマネジメントを終了処理
	manager->fbxsdk::FbxManager::Destroy();
}

//*****************************************************************************
//
// SDKマネジメントを初期化
//
//*****************************************************************************
HRESULT FbxSDK::InitFbxSDK()
{
	// SDKマネージャ生成
	manager = fbxsdk::FbxManager::Create();
	if (manager == NULL)
	{
		std::cout << "[Error] SDK Manager ... Fail!" << std::endl;
		return E_FAIL;
	}

	// FBXインポートを生成
	importer = fbxsdk::FbxImporter::Create(manager, "");
	if (manager == NULL)
	{
		std::cout << "[Error] SDK Manager ... Fail!" << std::endl;
		return E_FAIL;
	}
	
	// シーンを生成
	scene = fbxsdk::FbxScene::Create(manager, "");

	return S_OK;
}

//*****************************************************************************
//
// FBXモデルを読み込み
//
//*****************************************************************************
HRESULT FbxSDK::LoadFbx(std::string fbxPath)
{
	if (!importer->Initialize(fbxPath.c_str()))
	{
		std::cout << "[Error] Importer Initialize ... Fail!" << std::endl;
		return E_FAIL;
	}

	return S_OK;
}