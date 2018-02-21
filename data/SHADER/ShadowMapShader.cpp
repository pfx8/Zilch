//*****************************************************************************
//
// シャドーシェーダー[ShadowMapShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ShadowMapShader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ShadowMapShader::ShadowMapShader()
{
	this->effectPoint = NULL;
	this->shadowMapTex = NULL;
	this->shadeowMapShaderHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ShadowMapShader::~ShadowMapShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
HRESULT ShadowMapShader::InitShader()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadEffectFile();

	if (FAILED(pDevice->CreateTexture(512, 512,
		1, D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&this->shadowMapTex,
		NULL)))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
		return E_FAIL;
	}
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT ShadowMapShader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// ピクセル機能チェック
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// エラーバッファ
	D3DXCreateEffectFromFile(pDevice,
						"Shader/ShadowMapShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/ShadowMapShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<ShadowMapShader> Success!" << std::endl;

	return S_OK;
}