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

#include "../Engine.h"

class FbxSDK
{
private:
	FbxManager*  m_manager;	// SDKマネジメント
	FbxImporter* m_importer;	// FBX読み込みインポート
	FbxScene*	m_scene;		// シーン

public:
	FbxSDK();
	~FbxSDK();

	HRESULT InitFbxSDK();	// SDKマネジメントを初期化
};

#endif // !_FBX_SDK_H_


