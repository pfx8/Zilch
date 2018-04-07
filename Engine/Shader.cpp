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
	cout << endl << "<Shader> :" << endl;
	loadEffectFile(path);
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
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// ピクセル機能チェック
	{
		cout << "[Error] Don't support pixel shader!" << endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// エラーバッファ
	D3DXCreateEffectFromFile(pDevice,
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

	cout << "[Information] Loading <Shader> " << path << " ... success!" << endl;

	return S_OK;
}