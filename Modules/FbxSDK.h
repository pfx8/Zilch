//*****************************************************************************
//
// FbxSDK処理 [FbxSDK.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _FBX_SDK_H_
#define _FBX_SDK_H_

#include <fbxsdk.h>

#include "Mesh.h"
#include "..\Engine.h"

class FBX_SDK
{
private:
	FbxManager*	m_manager;	// SDKマネジメント
	FbxImporter*	m_importer;	// FBX読み込みインポート
	FbxNode*		m_rootnode;	// ルートノード
	FbxScene*	m_scene;		// シーン
	FbxMesh*		m_mesh;		// メッシュ

	void ProbeNode(FbxNode* node);	// シーンの下にあるFBXノードを探査
	bool LoadMaterial(FbxMesh* mesh);	// マテリアルを読み込み
public:
	FBX_SDK();
	~FBX_SDK();

	HRESULT InitFbxSDK();	// FbxSDKを初期化
	HRESULT LoadFbxScene(std::string fbxPath = " ");	// Fbxを読み込み
	HRESULT FbxMeshToDirectXMesh(DX_MESH* dxMesh);		// FbxデータをDXへ転送する
};

#endif // !_FBX_SDK_H_


