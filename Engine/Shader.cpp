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
Shader::Shader(wstring path)
{
	// パスからファイルの名前を取得(拡張子抜き)
	wstring name1 = path.substr(path.find_last_of(L"/") + 1, path.find_first_of(L"."));		// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	wstring name2 = name1.substr(0, name1.find_first_of(L"."));								// exp: ccc.fbx -> ccc

	loadEffectFile(path);

	// デフォルトはテクスチャモード
	this->mRenderingMode = RM_TEXTURE;

	// カラーランプモードを設定
	this->mColorRampType = CR_LINEAR;

	// セグメントを設定
	this->mColorRampSegment = D3DXVECTOR3(0.001f, 0.002f, 0.003f);

	// Debugウインドへ
	wcout << "<Scene> loading <Shader> " << path << " ... success!" << endl;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader(void)
{
	RELEASE_POINT(mEffect);
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::loadEffectFile(wstring path)
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
		wcout << "<Error> loading<Shader> " << path  << " ... fail!" << endl;					// エラーメッセージ
		wcout << "<Information> " << (char*)errorBuffer->GetBufferPointer() << endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	return S_OK;
}