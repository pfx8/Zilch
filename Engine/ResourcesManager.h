//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ResourcesManager
{
private:
	// テクスチャ
	std::map < std::string, std::string> textureList;	// テクスチャリスト
	std::string GetTextureStruct(std::string name);		// テクスチャパスを取得

	// メッシュ
	std::map < std::string, std::string> meshList;	// メッシュリスト
	std::string GetMeshPath(std::string name);		// メッシュパスを取得	

public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint);	// テクスチャを読み込み
	HRESULT LoadMesh(std::string name, Model* model);	// メッシュを読み込み
};

#endif // !_RESOURCES_MANAGER_H_

