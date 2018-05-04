//*****************************************************************************
//
// Shader処理 [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Shader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Shader::Shader(string path)
{
	string name = path.substr(path.find_last_of("//") + 1, path.find_last_of("/n"));
	cout << "<Shader> : "  << name;
	loadEffectFile(path);

	// デフォルトシェーディングモードを設定
	this->mRenderType = RT_TEXTURE;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(mEffect);
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::loadEffectFile(string path)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	D3DCAPS9 caps;
	pD3DDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// ピクセル機能チェック
	{
		cout << "[Error] Don't support pixel shader!" << endl;
	}

	ID3DXBuffer* errorBuffer = nullptr	;		// エラーバッファ
	D3DXCreateEffectFromFile(pD3DDevice,
						path.c_str(),	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->mEffect,		// エフェクトポインタ
						&errorBuffer);		// エラー情報

	if (errorBuffer)	// エラーをチェック
	{
		cout << "[Error] Loading <Shader> " << path  << " ... fail!" << endl;	// エラーメッセージ
		cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	cout << " loading ... success!" << endl;

	return S_OK;
}