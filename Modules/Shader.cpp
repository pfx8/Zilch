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
Shader::Shader()
{
	m_effectPoint = NULL;
	
	m_WVPMatrixHandle = NULL;
	m_basicShaderHandle = NULL;
	//m_texture1Handle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
void Shader::InitShader()
{
	// コンソールにメッセージを出す
	std::cout << std::endl << "<Shader>" << std::endl;
	LoadEffectFile();
	GetShaderTechniqueAndParameter();
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
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
						"Shader/BasicShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/BasicShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<BasicShader> Success!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// シェーダーを使うために、各設定をする
//
//*****************************************************************************
void Shader::GetShaderTechniqueAndParameter()
{
	// レンダリングのテクニックを取得
	m_basicShaderHandle = m_effectPoint->GetTechniqueByName("BasicShader");	// BasicShaderテクニックを設定

	// シェーダー中のグローバル変数を取得
	m_WVPMatrixHandle = m_effectPoint->GetParameterByName(0, "WVPMatrix");	// WVPマトリックス
	//m_texture1Handle = m_effectPoint->GetParameterByName(0, "Tex");			// テクスチャ


}