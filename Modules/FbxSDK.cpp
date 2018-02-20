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
	m_manager = NULL;
	m_importer = NULL;
	m_scene = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
FbxSDK::~FbxSDK()
{
	// SDKマネジメントを終了処理
	m_manager->fbxsdk::FbxManager::Destroy();
}

//*****************************************************************************
//
// SDKマネジメントを初期化
//
//*****************************************************************************
HRESULT FbxSDK::InitFbxSDK()
{
	// SDKマネージャ生成
	m_manager = fbxsdk::FbxManager::Create();
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}

	// FBXインポートを生成
	m_importer = fbxsdk::FbxImporter::Create(m_manager, "");
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}
	const char* filePath = "data/MODEL/lowP.fbx";
	if (!m_importer->Initialize(filePath)) 
	{
		std::cout << "[Error]Importer Initialize -- Failed!" << std::endl;
		return E_FAIL;
	}
	
	// シーンを生成
	m_scene = fbxsdk::FbxScene::Create(m_manager, "");
}