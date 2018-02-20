//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "CelShader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
CelShader::CelShader()
{
	this->effectPoint = NULL;
	this->celShaderHandle = NULL;
	this->WMatrixHandle = NULL;
	this->VPMatrixHandle = NULL;
	this->lightingHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
CelShader::~CelShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
void CelShader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT CelShader::LoadEffectFile()
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
						"Shader/CelShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/CelShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<CelShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// シェーダーを使うために、各設定をする
//
//*****************************************************************************
void CelShader::GetShaderParameter()
{
	// レンダリングのテクニックを取得
	this->celShaderHandle = this->effectPoint->GetTechniqueByName("CelShader");

	// シェーダー中のグローバル変数を取得
	this->WMatrixHandle = this->effectPoint->GetParameterByName(0, "WMatrix");
	this->VPMatrixHandle = this->effectPoint->GetParameterByName(0, "VPMatrix");
	this->typeHandle = this->effectPoint->GetParameterByName(0, "ObjType");
}