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
	FbxManager*		manager;	// SDKマネジメント
	FbxImporter*	importer;	// FBX読み込みインポート
	FbxScene*		scene;		// シーン

public:
	FbxSDK();
	~FbxSDK();

	HRESULT InitFbxSDK();					// SDKマネジメントを初期化
	HRESULT LoadFbx(std::string fbxPath);	// FBXモデルを読み込み
};

#endif // !_FBX_SDK_H_


