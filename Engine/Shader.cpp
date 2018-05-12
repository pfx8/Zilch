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
	// パスからファイルの名前を取得(拡張子抜き)
	string name1 = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	string name2 = name1.substr(0, name1.find_first_of("."));							// exp: ccc.fbx -> ccc

	loadEffectFile(path);

	// デフォルトシェーディングモードを設定
	this->mRenderMode = RT_TEXTURE;

	// カラーランプモードを設定
	this->mColorRamp = CR_LINEAR;

	// セグメントを設定
	this->mColorRampSegment = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		// Debugウインドへ
		cout << "<Error> don't support pixel shader!" << endl;
	}

	ID3DXBuffer* errorBuffer = nullptr;		// エラーバッファ
	D3DXCreateEffectFromFile(pD3DDevice,
						path.c_str(),		// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->mEffect,		// エフェクトポインタ
						&errorBuffer);		// エラー情報

	if (errorBuffer)	// エラーをチェック
	{
		// Debugウインドへ
		cout << "<Error> loading " << path  << " ... fail!" << endl;	// エラーメッセージ
		cout << "<Information> " << (char*)errorBuffer->GetBufferPointer() << endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// Debugウインドへ
	cout << "<Scene> loading " << path << " ... success!" << endl;

	return S_OK;
}