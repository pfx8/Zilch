//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ResourcesManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ResourcesManager::ResourcesManager()
{
	// テクスチャ検索マッピングを作る
	m_textureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	m_fbxList["scene00"] = "data/MODEL/FbxSDKmaterialtest.fbx";
	m_fbxList["scene01"] = "data/MODEL/FbxSDKtest.fbx";
	m_fbxList["testP"] = "data/MODEL/lowP.fbx";
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ResourcesManager::~ResourcesManager()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetTextureStruct(name).data() != "NULL")
	{
		// テクスチャを読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice, 
			GetTextureStruct(name).data(),
			texturePoint)))
		{
			std::cout << "[Error] Loading Texture<" << name << "> Failed!" << std::endl;	// コンソールにメッセージを出す
			return E_FAIL;
		}
		else
		{
			std::cout << "[Information] Loading Texture<" << name << "> Success!" << std::endl;	// コンソールにメッセージを出す
			return S_OK;
		}
	}
	else
	{
		*texturePoint = NULL;
		return S_OK;
	}
}


//*****************************************************************************
//
// テクスチャ構造体を取得
//
//*****************************************************************************
std::string ResourcesManager::GetTextureStruct(std::string name)
{
	if(m_textureList.find(name) != m_textureList.end())
	{
		return m_textureList[name];
	}
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
std::string ResourcesManager::GetFbxPath(std::string name)
{
	if (m_fbxList.find(name) != m_fbxList.end())
	{
		return m_fbxList[name];
	}

	return NULL;
}